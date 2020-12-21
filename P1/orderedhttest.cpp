#include <iostream>
#include <string>
#include <vector>

class PhoneNumber
{
public:
  PhoneNumber(std::string name, long number)
  {
    this->name = name;
    this->number = number;
    this->next = nullptr;
  }

  void set_name(std::string name)
  {
    this->name = name;
  }

  std::string get_name()
  {
    return this->name;
  }

  void set_number(long number)
  {
    this->number = number;
  }

  long get_number()
  {
    return this->number;
  }

  void set_next(PhoneNumber *next)
  {
    this->next = next;
  }

  PhoneNumber *get_next()
  {
    return this->next;
  }

private:
  std::string name;
  long number;
  PhoneNumber *next;
};

class Chain
{
public:
  Chain()
  {
    this->head = nullptr;
  }

  ~Chain()
  {
    while (head != nullptr)
    {
      PhoneNumber *node = head->get_next();
      delete head;
      head = node;
    }
    head = nullptr;
  }

  bool insert_number(std::string name, long number)
  {
    if (this->find_number(number))
    {
      return false;
    }

    PhoneNumber *num = new PhoneNumber(name, number);

    if (this->head == nullptr)
    {
      this->head = num;
    }
    else if (number < (this->head)->get_number())
    {
      PhoneNumber *tmp = this->head;
      this->head = num;
      num->set_next(tmp);
    }
    else
    {
      PhoneNumber *node = this->head;
      while (node->get_next() != NULL && (node->get_next())->get_number() < number)
      {
        node = node->get_next();
      }
      PhoneNumber *tmp = node->get_next();
      node->set_next(num);
      num->set_next(tmp);
    }
    return true;
  }

  PhoneNumber *find_number(long number)
  {
    PhoneNumber *tmp = this->head;
    while (tmp != nullptr && tmp->get_number() != number)
    {
      if (tmp->get_number() > number)
      {
        return nullptr;
      }
      tmp = tmp->get_next();
    }

    return tmp;
  }

  bool delete_number(long number)
  {
    if (!this->find_number(number))
    {
      return false;
    }

    PhoneNumber *node = this->head;

    if (node->get_number() == number)
    {
      this->head = node->get_next();
    }
    else
    {
      while ((node->get_next())->get_number() != number)
      {
        node = node->get_next();
      }
      PhoneNumber *tmp = node->get_next();
      node->set_next(tmp->get_next());
      node = tmp;
    }
    //delete the node.
    delete node;
    return true;
  }

  void print_chain()
  {
    if (this->head == nullptr)
    {
      return;
    }

    PhoneNumber *node = this->head;

    while (node != nullptr)
    {
      std::cout << node->get_number() << " ";
      node = node->get_next();
    }

    std::cout << std::endl;
  }

private:
  PhoneNumber *head;
};

class Hashtable
{
public:
  Hashtable(std::size_t m)
  {
    this->size = m;
    this->Table = std::vector<Chain>(m);
    std::cout << "success" << std::endl;
  }

  void i(std::string name, long number)
  {
    bool result = this->Table[number % size].insert_number(name, number);
    if (result)
    {
      std::cout << "success" << std::endl;
    }
    else
    {
      std::cout << "failure" << std::endl;
    }
  }

  void s(long number)
  {
    std::size_t p = number % this->size;
    PhoneNumber *val = Table[p].find_number(number);
    if (val)
    {
      std::cout << "found " << val->get_name() << " in " << p << std::endl;
    }
    else
    {
      std::cout << "not found" << std::endl;
    }
  }

  void d(long number)
  {
    std::size_t p = number % this->size;
    bool deleted = Table[p].delete_number(number);
    if (deleted)
    {
      std::cout << "success" << std::endl;
    }
    else
    {
      std::cout << "failure" << std::endl;
    }
  }

  void p(std::size_t i)
  {
    Table[i].print_chain();
  }

  std::vector<Chain> Table;
  std::size_t size;
};

int main()
{
  std::string cmdline;
  getline(std::cin, cmdline);
  Hashtable *test = nullptr;

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
        test = new Hashtable(m);
      }
      else if (cmd == "i")
      {
        std::size_t semi = cmdline.find(';');
        long number = std::stol(cmdline.substr(0, semi));
        std::string name = cmdline.substr(semi + 1);
        test->i(name, number);
      }
      else if (cmd == "s")
      {
        long number = std::stol(cmdline);
        test->s(number);
      }
      else if (cmd == "d")
      {
        long number = std::stol(cmdline);
        test->d(number);
      }
      else if (cmd == "p")
      {
        std::size_t number = std::stol(cmdline);
        test->p(number);
      }

      getline(std::cin, cmdline);
    }
  }

  return 0;
}
