#include "MyString.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <algorithm>

MyString::MyString(const char* rawString) {
    this->_size = 0;
    this->_data = nullptr;
    if (rawString != nullptr) {
        _size = std::strlen(rawString);
        _data = new char[_size];
        for (size_t i = 0; i < _size; i++) {
            _data[i] = rawString[i];
        }
    }
}

MyString::MyString(const MyString& other) {
    this->_size = other._size;
    this->_data = new char[other._size];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = other[i];
    }
}

MyString::MyString(MyString&& other) noexcept {
    this->_size = other._size;
    this->_data = other._data;
    other._size = 0;
    other._data = nullptr;
}

MyString& MyString::operator=(const MyString& other) {
    this->_size = other._size;
    delete[] _data;
    this->_data = nullptr;
    if (other._size != 0) {
        this->_data = new char[other._size];
        for (size_t i = 0; i < _size; i++) {
            _data[i] = other[i];
        }
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    this->_size = other._size;
    std::swap(this->_data, other._data);
    delete[] other._data;
    other._data = nullptr;
    other._size = 0;
    return *this;
}

MyString::~MyString() {
    this->_size = 0;
    delete[] this->_data;
    this->_data = nullptr;
}

char& MyString::at(const unsigned int idx) {
    assert(idx < _size);
    return _data[idx];
}

const char& MyString::at(const unsigned int idx) const {
    assert(idx < _size);
    return _data[idx];
}


void MyString::append(const MyString& appendedString) {
    this->insert(_size, appendedString);
}

void MyString::insert(unsigned int pos, const MyString& insertedString) {
    assert(pos <= _size);
    char* newData = new char[this->_size + insertedString._size];
    for (size_t i = 0; i < _size; i++) {
        newData[i] = _data[i];
    }
    for (int i = (int)(_size + insertedString._size) - 1; i >= (int)(pos + insertedString._size); i--) {
        newData[i] = this->at(i - insertedString._size);
    }
    for (size_t i = pos; i < pos + insertedString._size; i++) {
        newData[i] = insertedString[i - pos];
    }
    this->_size += insertedString._size;
    delete[] this->_data;
    this->_data = newData;
}

void MyString::clear() {
    delete[] this->_data;
    this->_size = 0;
    this->_data = nullptr;
}

void MyString::erase(unsigned int pos, unsigned int count) {
    assert(pos <= _size);
    size_t realCount = count;
    if (count > _size - pos) {
        realCount = this->size() - pos;
    }
    char* newData = new char[this->_size - realCount];
    for (size_t i = 0; i < _size - realCount; i++) {
        newData[i] = _data[i];
    }
    for (int i = (int)(_size - realCount) - 1; i >= (int)pos; i--) {
        newData[i] = _data[i + realCount];
    }
    this->_size -= realCount;
    delete[] this->_data;
    this->_data = nullptr;
    if (this->_size != 0) {
        this->_data = newData;
    }
}

unsigned int MyString::size() const {
    return this->_size;
}

bool MyString::isEmpty() const {
    return this->_size == 0;
}

const char* MyString::rawString() const {
    char* resString = new char[this->_size + 1];
    for (size_t i = 0; i < _size; i++) {
        resString[i] = _data[i];
    }
    resString[_size] = '\0';
    return resString;
}

unsigned int MyString::find(const MyString& substring, const unsigned int pos) {
    assert(pos <= _size);
    for (size_t i = pos; i < _size - substring._size + 1; i++) {
        bool equal = true;
        for (size_t j = i; j < i + substring._size; j++) {
            if (_data[j] != substring[j - i]) {
                equal = false;
                break;
            }
        }
        if (equal) {
            return i;
        }
    }
    return -1;
}

int MyString::compare(const MyString& comparableString) const {
	if (this->_size > comparableString._size) {
		return 1;
	}
	else if (this->_size < comparableString._size) {
		return -1;
	}

	for (size_t i = 0; i < this->_size; ++i) {
		if (this->_data[i] > comparableString._data[i]) {
			return 1;
		}
		else if (this->_data[i] < comparableString._data[i]) {
			return -1;
		}
	}
	return 0;
}

char& MyString::operator[](const unsigned int idx) {
    return at(idx);
}

const char& MyString::operator[](const unsigned int idx) const {
    return at(idx);
}

MyString& MyString::operator+(const MyString& appendedString) {
    this->append(appendedString);
    return *this;
}

bool MyString::operator==(const MyString& comparableString) const {
    return (this->compare(comparableString) == 0);
}
bool MyString::operator!=(const MyString& comparableString) const {
    return !(*this == comparableString);
}
bool MyString::operator>(const MyString& comparableString) const {
    return (this->compare(comparableString) > 0);
}
bool MyString::operator<(const MyString& comparableString) const {
    return (this->compare(comparableString) < 0);
}
bool MyString::operator>=(const MyString& comparableString) const {
    return (*this > comparableString || *this == comparableString);
}
bool MyString::operator<=(const MyString& comparableString) const {
    return !(*this >= comparableString);
}
