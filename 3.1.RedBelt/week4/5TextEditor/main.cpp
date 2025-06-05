#include <string>
#include <list>
#include <vector>
#include <iterator>
//#include <algorithm>

#include "test_runner.h"
#include "profile.h"

using namespace std;

class Editor {
    list<char> text_;
    vector<char> buffer_;
    list<char>::iterator it_pos;

 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor() : text_({}), buffer_({}), it_pos(text_.begin())
  {
  }

  void Left() {
    if (it_pos != text_.begin() || !text_.empty()) {
        --it_pos;
    }
  }

  void Right() {
    if (it_pos != prev(text_.end()) || !text_.empty()) {
        ++it_pos;
    }
  }

  void Insert(char token) {
    text_.insert(it_pos, token);
  }

  void Cut(size_t tokens = 1) {
    Copy(tokens);
    auto iter = it_pos;
    while (iter != text_.end() && tokens > 0)
    {
        iter = text_.erase(iter);
        --tokens;
    }
    it_pos = iter;
  }

  void Copy(size_t tokens = 1) {
    buffer_.clear();
    auto iter = it_pos;
    if (!text_.empty() || iter != text_.end()) {
        while (tokens > 0 && iter != text_.end())
        {
            buffer_.push_back(*iter++);
            --tokens;
        }
    } 
  }

  void Paste() {
    for (auto ch : buffer_) {
    text_.insert(it_pos, ch);
    }
  }

  string GetText() const {
    string s;
    for (const auto ch : text_) {
        s+=ch;
    }
    return s;
  }
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}
 
void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}
 
void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}
  
void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);

    return 0;
}

/* 
// Printing with '|' sign!!!!!!!!!!!!!!!!!!!!!!!
#include <string>
#include <list>
#include <vector>
#include <iterator>
//#include <algorithm>

#include "test_runner.h"
#include "profile.h"

using namespace std;

class Editor {
    list<char> text_;
    vector<char> buffer_;
    list<char>::iterator it_pos;

 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor() : text_({'|'}), buffer_({}), it_pos(text_.begin())
  {
  }

  void Left() {
    if (it_pos != text_.begin() || !text_.empty()) {
        text_.erase(it_pos--);
        it_pos = text_.insert(it_pos, '|');
    }
  }

  void Right() {
    if (it_pos != prev(text_.end()) || !text_.empty()) {
        text_.erase(it_pos++);
        it_pos = text_.insert(++it_pos, '|');
    }
  }

  void Insert(char token) {
    text_.insert(it_pos, token);
  }

  void Cut(size_t tokens = 1) {
    buffer_.clear();
    Copy(tokens);
    auto iter = next(it_pos);
    while (iter != text_.end() && tokens > 0)
    {
        iter = text_.erase(iter);
        --tokens;
    }
    
  }

  void Copy(size_t tokens = 1) {
    buffer_.clear();
    auto iter = next(it_pos);
    if (!text_.empty() || iter != text_.end()) {
        while (tokens > 0 && iter != text_.end())
        {
            buffer_.push_back(*iter++);
            --tokens;
        }
    } 
  }

  void Paste() {
    for (auto ch : buffer_) {
    text_.insert(it_pos, ch);
    }
  }

  string GetText() const {
    string s;
    cout << '`';
    for (const auto ch : text_) {
        s+=ch;
        cout << ch;
    }
    cout << '`' << endl;
    return s;
  }
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    //editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}
 
void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}
 
void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}
  
void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    //RUN_TEST(tr, TestReverse);
    //RUN_TEST(tr, TestNoText);
    //RUN_TEST(tr, TestEmptyBuffer);

    Editor editor;
    const string text = "hello, world";
    for (char c : text) {
        editor.Insert(c);
    }
    editor.GetText();
    // Текущее состояние редактора: `hello, world|`
    for (size_t i = 0; i < text.size(); ++i) {
        editor.Left();
    }
    editor.GetText();
    editor.Copy(5);
    editor.Cut(7);
    editor.GetText();
    for (size_t i = 0; i < 5; ++i) {
        editor.Right();
    }
    editor.GetText();
    editor.Insert(',');
    editor.Insert(' ');
    editor.GetText();
    editor.Paste();
    editor.GetText();
    editor.Left();
    editor.Left();
    editor.GetText();
    editor.Cut(3);
    cout << editor.GetText();
    return 0;
}
 */