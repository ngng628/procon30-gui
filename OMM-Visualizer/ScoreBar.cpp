# include "ScoreBar.h"

void ScoreBar::draw(const Font& font, int32 red_score, int32 blue_score) const
{
	m_rect.draw(Color(U"#205EE3"));
	m_rect.drawFrame(0, 3);
	const double rate = static_cast<double>(red_score) / (red_score + blue_score);
	RectF(m_rect.pos, m_rect.w * rate, m_rect.h).draw(Color(U"#E2421F"));

	font(red_score).draw(m_rect.x, m_rect.y + m_rect.h + 5);
	DrawableText blue_text = font(blue_score);
	font(blue_score).draw(m_rect.x + m_rect.w - blue_text.region().w, m_rect.y + m_rect.h + 5);
}
