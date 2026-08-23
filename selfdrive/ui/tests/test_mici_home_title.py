import pyray as rl

from openpilot.selfdrive.ui.mici.layouts import home


def test_compasspilot_home_title_scales_to_fit(monkeypatch):
  monkeypatch.setattr(home.gui_app, "font", lambda _weight: object())
  monkeypatch.setattr(home, "measure_text_cached", lambda _font, text, font_size: rl.Vector2(len(text) * font_size, font_size))

  font_size = home.fitted_home_title_font_size("CompassPilot", home.FontWeight.BRAND)

  assert font_size == 40
  assert len("CompassPilot") * font_size <= home.HOME_TITLE_MAX_WIDTH


def test_short_home_title_keeps_full_font_size(monkeypatch):
  monkeypatch.setattr(home.gui_app, "font", lambda _weight: object())
  monkeypatch.setattr(home, "measure_text_cached", lambda _font, text, font_size: rl.Vector2(len(text) * font_size, font_size))

  assert home.fitted_home_title_font_size("Pilot", home.FontWeight.BRAND) == home.HOME_TITLE_MAX_FONT_SIZE
