import tarfile

import zstandard as zstd

from openpilot.starpilot.common import starpilot_backups as backups


class FakeParams:
  def __init__(self, onroad=False):
    self.onroad = onroad
    self.values = {}

  def get_bool(self, key):
    assert key == "IsOnroad"
    return self.onroad

  def put(self, key, value):
    self.values[key] = value


class OnroadAfterWrites(FakeParams):
  def __init__(self, offroad_writes):
    super().__init__(onroad=False)
    self.offroad_writes = offroad_writes
    self.write_checks = 0

  def get_bool(self, key):
    self.write_checks += 1
    return self.write_checks > self.offroad_writes


class CountingParams(FakeParams):
  def __init__(self):
    super().__init__(onroad=False)
    self.write_checks = 0

  def get_bool(self, key):
    self.write_checks += 1
    return False


def test_automatic_backup_cancels_onroad_and_restarts_cleanly(tmp_path):
  source = tmp_path / "source"
  source.mkdir()
  (source / "file.bin").write_bytes(b"x" * 100_000)
  destination = tmp_path / "automatic"
  params = OnroadAfterWrites(offroad_writes=3)

  assert backups.create_backup(source, destination, "done", "failed", params, compressed=True) is False
  assert params.write_checks > 3
  assert not (tmp_path / "automatic_in_progress.tar.zst").exists()
  assert not (tmp_path / "automatic.tar.zst").exists()

  offroad_params = FakeParams(onroad=False)
  assert backups.create_backup(source, destination, "done", "failed", offroad_params, compressed=True) is True
  assert not (tmp_path / "automatic_in_progress.tar.zst").exists()

  with (tmp_path / "automatic.tar.zst").open("rb") as compressed_file:
    with zstd.ZstdDecompressor().stream_reader(compressed_file) as reader:
      with tarfile.open(fileobj=reader, mode="r|") as archive:
        archived_file = next(member for member in archive if member.name == "automatic/file.bin")
        assert archive.extractfile(archived_file).read() == b"x" * 100_000


def test_automatic_backup_checks_onroad_after_compressor_finalization(tmp_path):
  source = tmp_path / "source"
  source.mkdir()
  (source / "file.bin").write_bytes(b"x" * 100_000)
  destination = tmp_path / "automatic"

  counting_params = CountingParams()
  assert backups.create_backup(source, destination, "done", "failed", counting_params, compressed=True) is True
  (tmp_path / "automatic.tar.zst").unlink()

  params = OnroadAfterWrites(offroad_writes=counting_params.write_checks - 1)
  assert backups.create_backup(source, destination, "done", "failed", params, compressed=True) is False
  assert not (tmp_path / "automatic_in_progress.tar.zst").exists()
  assert not (tmp_path / "automatic.tar.zst").exists()


def test_automatic_backup_does_not_start_onroad(monkeypatch):
  def fail_if_called(*args):
    raise AssertionError("backup started")

  monkeypatch.setattr(backups, "cleanup_backups", fail_if_called)

  assert backups.backup_starpilot(None, FakeParams(onroad=True)) is False
