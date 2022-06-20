DerivatedClass &	DerivatedClass::operator=(const DerivatedClass & src) {
	BaseClass1::operator=(src);
	BaseClass2::operator=(src);
	this->attribute = src.attribute;
	return *this;
}
