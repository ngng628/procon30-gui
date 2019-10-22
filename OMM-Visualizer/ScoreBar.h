# pragma once
# include "Field.h"

class ScoreBar
{
private:

	RectF m_rect;

public:

	ScoreBar() = default;

	explicit ScoreBar(const RectF& rect)
		: m_rect(rect) {}

	void draw(const Font& font, const Field& field) const;
};

