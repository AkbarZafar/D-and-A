#include <iostream>
#include <string>
#include <vector>

class PhoneNumber
{
public:
  PhoneNumber()
  {
    number = -1;
  }

  PhoneNumber(std::string name, long number)
  {
    this->number = number;
    this->name = name;
  }

  long get_number()
  {
    return number;
  }

  void set_number(long number)
  {
    this->number = number;
  }

  std::string get_name()
  {
    return this->name;
  }

  void set_name(std::string name)
  {
    this->name = name;
  }

private:
  long number;
  std::string name;
};

class HashTable
{
public:
  HashTable(std::size_t m)
  {
    this->size = m;
    this->Table = std::vector<PhoneNumber>(m);
    std::cout << "success" << std::endl;
  }

  void search(long number)
  {
    std::size_t index = number % size;
    std::size_t i = 1;
    std::size_t offset = (number / size) % size;
    if (offset % 2 == 0)
    {
      offset++;
    }
    while (Table[index].get_number() != number)
    {
      int offset = (i * (number / size)) % size;
      if (offset % 2 == 0)
      {
        offset++;
      }
      index = (index + (i * offset)) % size;
      i++;
      if (i > size || Table[index].get_number() == -1)
      {
        std::cout << "not found" << std::endl;
        return;
      }
    }
    std::cout << "found " << Table[index].get_name() << " in " << index << std::endl;
  }

  void insert(std::string name, long number)
  {
    std::size_t index = number % size;
    std::size_t i = 1;
    std::size_t offset = (number / size) % size;

    if (offset % 2 == 0)
    {
      offset++;
    }
    while (Table[index].get_number() != -1)
    {
      index = (index + (i * offset)) % size;
      i++;
      if (i > size || Table[index].get_number() == number)
      {
        std::cout << "failure" << std::endl;
        return;
      }
    }

    index = number % size;
    i = 1;
    while (Table[index].get_number() > 0)
    {
      index = (index + (i * offset)) % size;
      i++;
    }
    Table[index] = PhoneNumber(name, number);
    std::cout << "success" << std::endl;
  }

  void deleter(long number)
  {
    std::size_t index = number % size;
    std::size_t i = 1;
    std::size_t offset = (number / size) % size;
    if (offset % 2 == 0)
    {
      offset++;
    }
    while (Table[index].get_number() != number)
    {
      index = (index + (i * offset)) % size;
      i++;
      if (i > size || Table[index].get_number() == -1)
      {
        std::cout << "failure" << std::endl;
        return;
      }
    }

    Table[index].set_number(-2);
    std::cout << "success" << std::endl;
  }

  std::vector<PhoneNumber> Table;
  std::size_t size;
};

int main()
{
  std::string cmdline;
  getline(std::cin, cmdline);
  HashTable *test = nullptr;

  while (!std::cin.eof())
  {
    if (cmdline == "exit")
    {
      delete test;
      test = nullptr;
      return 0;
    }
    else
    {
      std::size_t commandindex = cmdline.find(' ');

      std::string cmd = cmdline.substr(0, commandindex);
      cmdline = cmdline.substr(commandindex + 1);

      if (cmd == "n")
      {
        if (test != nullptr)
        {
          delete test;
          test = nullptr;
        }
        std::size_t m = std::stoi(cmdline);
        test = new HashTable(m);
      }
      else if (cmd == "i")
      {
        std::size_t semi = cmdline.find(';');
        long number = std::stol(cmdline.substr(0, semi));
        std::string name = cmdline.substr(semi + 1);
        test->insert(name, number);
      }
      else if (cmd == "s")
      {
        long number = std::stol(cmdline);
        test->search(number);
      }
      else if (cmd == "d")
      {
        long number = std::stol(cmdline);
        test->deleter(number);
      }

      getline(std::cin, cmdline);
    }
  }

  return 0;
}
