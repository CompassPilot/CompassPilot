"""A drive the route reader refuses must not crash steerlearnerd (device crash loop, 2026-11-11)."""
import pytest

from openpilot.starpilot.flm.offroad_daemon import ANALYSIS_ERRORS
from openpilot.starpilot.flm.offroad_route import walk_completed_route


def _route(*, rlog_missing_at=None):
  route_id = '0000004a--1b2c3d4e5f'
  segments = []
  for number in range(3):
    present = number != rlog_missing_at
    segments.append({'number': number, 'segmentName': f'{route_id}--{number}', 'files': {'qlog': present, 'rlog': present}})
  return {'routeId': route_id, 'segmentCount': len(segments), 'segments': segments}


def test_route_with_missing_segment_logs_is_a_handled_analysis_refusal(tmp_path):
  with pytest.raises(ANALYSIS_ERRORS, match='missing segments or logs'):
    walk_completed_route(tmp_path, _route(rlog_missing_at=1), permitted=lambda: True, consume=lambda *a, **k: None)
