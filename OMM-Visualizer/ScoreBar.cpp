# include "ScoreBar.h"
# include "ScoreCalculate.h"

void ScoreBar::draw(const Font& font, const Field& field) const
{
	int32 red_score = ScoreCalculate(field.points, field.normalizedTiled(0));
	int32 blue_score = ScoreCalculate(field.points, field.normalizedTiled(1));

	m_rect.draw(Color(U"#205EE3"));
	m_rect.drawFrame(0, 3);

	auto calcRate = [&](int32 red, int32 blue)
	{
		if (red < 0 and blue < 0)
		{
			int32 tmp = -red;
			red = -blue;
			blue = tmp;
		}
		double maxi = std::max(1, std::max(red, blue) + 10);
		double mini = std::min(0, std::min(red, blue) - 10);
		double r = ((double)(red)-mini) / (maxi - mini);
		double b = ((double)(blue)-mini) / (maxi - mini);
		return r / (r + b);
	};

	const double rate = calcRate(red_score, blue_score);
	RectF(m_rect.pos, m_rect.w * rate, m_rect.h).draw(Color(U"#E2421F"));

	font(red_score).draw(m_rect.x, m_rect.y + m_rect.h + 5);
	DrawableText blue_text = font(blue_score);
	font(blue_score).draw(m_rect.x + m_rect.w - blue_text.region().w, m_rect.y + m_rect.h + 5);
}
