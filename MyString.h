#pragma once

class MyString
{
public:

    MyString(const char* rawString = nullptr);
    explicit MyString(const MyString& other);
    MyString(MyString&& other) noexcept;
    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;

    ~MyString();

    void append(const MyString& appendedString);
    void insert(unsigned int pos, const MyString& insertedString);
    void clear();
    void erase(unsigned int pos, unsigned int count);
    char& at(unsigned int idx);
    const char& at(unsigned int idx) const;
    unsigned int size() const;
    bool isEmpty() const;
    const char* rawString() const;
    unsigned int find(const MyString& substring, unsigned int pos = 0);
    int compare(const MyString& comparableString) const;

    char& operator[](unsigned int idx);
    const char& operator[](unsigned int idx) const;
    MyString& operator+(const MyString& appendedString);

    bool operator==(const MyString& comparableString) const;
    bool operator!=(const MyString& comparableString) const;
    bool operator>(const MyString& comparableString) const;
    bool operator<(const MyString& comparableString) const;
    bool operator>=(const MyString& comparableString) const;
    bool operator<=(const MyString& comparableString) const;

private:
    char* _data;
    unsigned int _size;
};
