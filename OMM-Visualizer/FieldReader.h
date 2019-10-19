# pragma once
# include "Field.h"
# include "picojson/picojson.h"

class FieldReader
{
public:
	FieldReader() = default;
	FieldReader(const FilePath& path);

	bool copyTo(Field& field);

private:
	picojson::value init_value;
	Field m_field;
};

