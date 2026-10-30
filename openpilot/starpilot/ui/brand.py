"""User-facing StarPilot identity, separate from upstream build metadata."""

DISPLAY_VERSION = "7.0"
BRAND_NAME = "CompassPilot"
HOME_SCREEN_NAME_MAX_LENGTH = 12


def home_screen_name(value: str | bytes | None) -> str:
  """The saved home screen title, limited to the brand atlas' printable ASCII glyphs."""
  if isinstance(value, bytes):
    value = value.decode("utf-8", errors="ignore")
  name = "".join(char for char in str(value or "") if 32 <= ord(char) < 127).strip()[:HOME_SCREEN_NAME_MAX_LENGTH]
  return name or BRAND_NAME


def home_description(updater_description: str) -> str:
  """Keep branch/detail suffixes without showing the upstream base version."""
  if not updater_description:
    return DISPLAY_VERSION
  parts = updater_description.split(" / ")
  parts[0] = DISPLAY_VERSION
  return " / ".join(parts)
