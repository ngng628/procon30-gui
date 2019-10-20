# pragma once

class ScoreBar
{
private:

	RectF m_rect;

public:

	ScoreBar() = default;

	explicit ScoreBar(const RectF& rect)
		: m_rect(rect) {}

	void draw(const Font& font, int32 red_score, int32 blue_score) const;
};

