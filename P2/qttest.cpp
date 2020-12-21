#include <iostream>
#include <iomanip>

class Node
{
public:
  double x; // longtitude
  double y; // latitude
  std::string city_name;
  int population;
  double cost_of_living;
  double net_salary;

  Node *NW;
  Node *NE;
  Node *SW;
  Node *SE;

  Node(double x, double y, std::string city_name, int population, double cost_of_living, double net_salary)
  {
    this->x = x;
    this->y = y;
    this->city_name = city_name;
    this->population = population;
    this->cost_of_living = cost_of_living;
    this->net_salary = net_salary;

    //set default values of child nodes to null.
    NW = nullptr;
    NE = nullptr;
    SW = nullptr;
    SE = nullptr;
  }
};

class QuadTree
{
public:
  Node *root;
  int count;

  QuadTree()
  {
    root = nullptr;
    count = 0;
  }

  ~QuadTree()
  {
    //deallocate all nodes
    recClear(root);
    root = nullptr;
    count = 0;
  }

  void recClear(Node *node)
  {
    if (node == nullptr)
    {
      return;
    }
    //look in all directions, if a node was used, deallocate.
    recClear(node->NE);
    recClear(node->NW);
    recClear(node->SW);
    recClear(node->SE);
    delete node;
    node = nullptr;
  }

  std::string get_direction(Node *node, double x, double y)
  {
    if (x >= node->x && y > node->y)
    {
      return "NE";
    }
    if (x < node->x && y >= node->y)
    {
      return "NW";
    }
    if (x <= node->x && y < node->y)
    {
      return "SW";
    }
    if (x > node->x && y <= node->y)
    {
      return "SE";
    }
    std::cout << "error in get_direction" << std::endl;
    return "";
  }

  Node *next_direction(Node *node, std::string direction)
  {
    Node *next;
    if (direction == "NE")
    {
      next = node->NE;
    }
    else if (direction == "NW")
    {
      next = node->NW;
    }
    else if (direction == "SW")
    {
      next = node->SW;
    }
    else if (direction == "SE")
    {
      next = node->SE;
    }

    return next;
  }

  double get_attr(Node *node, char attr)
  {
    if (attr == 'p')
    {
      return (double)(node->population);
    }
    else if (attr == 'r')
    {
      return node->cost_of_living;
    }
    else if (attr == 's')
    {
      return node->net_salary;
    }
    std::cout << "failure in get_attr function, value of attr: " << attr << std::endl;
    return -1;
  }

  double rec_max_find(Node *node, double max, char attr)
  {

    if (node == nullptr)
    {
      return max;
    }

    return std::max(get_attr(node, attr),
                    std::max(max = rec_max_find(node->NW, max, attr),
                             std::max(max = rec_max_find(node->NE, max, attr),
                                      std::max(max = rec_max_find(node->SW, max, attr),
                                               rec_max_find(node->SE, max, attr)))));
  }

  double rec_total_find(Node *node, char attr)
  {
    if (node == nullptr)
    {
      return 0;
    }

    return get_attr(node, attr) +
           rec_total_find(node->NW, attr) +
           rec_total_find(node->NE, attr) +
           rec_total_find(node->SW, attr) +
           rec_total_find(node->SE, attr);
  }

  double rec_min_find(Node *node, double min, char attr)
  {
    if (node == nullptr)
    {
      return min;
    }

    return std::min(get_attr(node, attr),
                    std::min(min = rec_min_find(node->NW, min, attr),
                             std::min(min = rec_min_find(node->NE, min, attr),
                                      std::min(min = rec_min_find(node->SW, min, attr),
                                               rec_min_find(node->SE, min, attr)))));
  }

  std::string recPrint(Node *node)
  {
    if (node == nullptr)
    {
      return "";
    }
    return recPrint(node->NE) + recPrint(node->NW) + node->city_name + " " + recPrint(node->SW) + recPrint(node->SE);
  }

  void recinsert(Node *node, Node *insertNode)
  {
    if (node->x == insertNode->x && node->y == insertNode->y)
    {
      delete insertNode;
      insertNode = nullptr;
      std::cout << "failure" << std::endl;
      return;
    }

    std::string direction = get_direction(node, insertNode->x, insertNode->y);
    Node *next = next_direction(node, direction);
    if (next == nullptr)
    {
      if (direction == "NE")
      {
        node->NE = insertNode;
      }
      else if (direction == "NW")
      {
        node->NW = insertNode;
      }
      else if (direction == "SW")
      {
        node->SW = insertNode;
      }
      else if (direction == "SE")
      {
        node->SE = insertNode;
      }
      count++;
      std::cout << "success" << std::endl;
    }
    else
    {
      recinsert(next, insertNode);
    }
  }

  Node *recsearch(Node *node, double x, double y)
  {
    if (node == nullptr)
    {
      return nullptr;
    }

    if (node->x == x && node->y == y)
    {
      return node;
    }
    std::string direction = get_direction(node, x, y);
    Node *next = next_direction(node, direction);

    // if (next == nullptr)
    // {
    //   return nullptr;
    // }

    return recsearch(next, x, y);
  }
};

int main()
{
  std::string cmdline;
  getline(std::cin, cmdline);
  QuadTree *tree = new QuadTree();

  while (!std::cin.eof())
  {
    if (cmdline == "exit")
    {
      delete tree;
      tree = nullptr;
      return 0;
    }
    else
    {
      std::size_t commandindex = cmdline.find(' ');

      std::string cmd = cmdline.substr(0, commandindex);
      cmdline = cmdline.substr(commandindex + 1);

      if (cmd == "size")
      {
        std::cout << "tree size " << tree->count << std::endl;
      }
      else if (cmd == "i")
      {
        std::size_t semi = cmdline.find(';');
        std::string city_name = cmdline.substr(0, semi);

        cmdline = cmdline.substr(semi + 1);
        semi = cmdline.find(';');
        double x = std::stod(cmdline.substr(0, semi));

        cmdline = cmdline.substr(semi + 1);
        semi = cmdline.find(';');
        double y = std::stod(cmdline.substr(0, semi));

        cmdline = cmdline.substr(semi + 1);
        semi = cmdline.find(';');
        double population = std::stoi(cmdline.substr(0, semi));

        cmdline = cmdline.substr(semi + 1);
        semi = cmdline.find(';');
        double cost_of_living = std::stod(cmdline.substr(0, semi));

        double net_salary = std::stod(cmdline.substr(semi + 1));

        Node *insert = new Node(x, y, city_name, population, cost_of_living, net_salary);
        if (tree->root == nullptr)
        {
          tree->root = insert;
          tree->count++;
          std::cout << "success" << std::endl;
        }
        else
        {
          tree->recinsert(tree->root, insert);
        }
      }
      else if (cmd == "s")
      {
        std::size_t semi = cmdline.find(';');
        double x = std::stod(cmdline.substr(0, semi));
        double y = std::stod(cmdline.substr(semi + 1));

        Node *node = (tree->recsearch(tree->root, x, y));
        if (node == nullptr)
        {
          std::cout << "not found" << std::endl;
        }
        else
        {
          std::cout << "found " << node->city_name << std::endl;
        }
      }
      else if (cmd == "q_max")
      {
        std::size_t semi = cmdline.find(';');
        double x = std::stod(cmdline.substr(0, semi));

        cmdline = cmdline.substr(semi + 1);
        semi = cmdline.find(';');
        double y = std::stod(cmdline.substr(0, semi));

        cmdline = cmdline.substr(semi + 1);
        semi = cmdline.find(';');
        std::string direction = cmdline.substr(0, semi);

        char attr = (cmdline.substr(semi + 1))[0];

        Node *node = tree->recsearch(tree->root, x, y);
        if (node == nullptr || tree->next_direction(node, direction) == nullptr)
        {
          std::cout << "failure" << std::endl;
        }
        else
        {
          Node *next = tree->next_direction(node, direction);
          double max = tree->get_attr(next, attr);
          double ans = tree->rec_max_find(next, max, attr);
          if (attr == 'p')
          {
            std::cout << "max " << (int)ans << std::endl;
          }
          else
          {
            std::cout << std::fixed << std::setprecision(2) << "max " << ans << std::endl;
          }
        }
      }
      else if (cmd == "q_min")
      {
        std::size_t semi = cmdline.find(';');
        double x = std::stod(cmdline.substr(0, semi));

        cmdline = cmdline.substr(semi + 1);
        semi = cmdline.find(';');
        double y = std::stod(cmdline.substr(0, semi));

        cmdline = cmdline.substr(semi + 1);
        semi = cmdline.find(';');
        std::string direction = cmdline.substr(0, semi);

        char attr = (cmdline.substr(semi + 1))[0];

        Node *node = tree->recsearch(tree->root, x, y);
        if (node == nullptr || tree->next_direction(node, direction) == nullptr)
        {
          std::cout << "failure" << std::endl;
        }
        else
        {
          Node *next = tree->next_direction(node, direction);
          double min = tree->get_attr(next, attr);
          double ans = tree->rec_min_find(next, min, attr);
          if (attr == 'p')
          {
            std::cout << "min " << (int)ans << std::endl;
          }
          else
          {
            std::cout << std::fixed << std::setprecision(2) << "min " << ans << std::endl;
          }
        }
      }
      else if (cmd == "q_total")
      {
        std::size_t semi = cmdline.find(';');
        double x = std::stod(cmdline.substr(0, semi));

        cmdline = cmdline.substr(semi + 1);
        semi = cmdline.find(';');
        double y = std::stod(cmdline.substr(0, semi));

        cmdline = cmdline.substr(semi + 1);
        semi = cmdline.find(';');
        std::string direction = cmdline.substr(0, semi);

        char attr = (cmdline.substr(semi + 1))[0];

        Node *node = tree->recsearch(tree->root, x, y);

        if (node == nullptr || tree->next_direction(node, direction) == nullptr)
        {
          std::cout << "failure" << std::endl;
        }
        else
        {
          Node *next = tree->next_direction(node, direction);
          double ans = tree->rec_total_find(next, attr);
          if (attr == 'p')
          {
            std::cout << "total " << (int)ans << std::endl;
          }
          else
          {
            std::cout << std::fixed << std::setprecision(2) << "total " << ans << std::endl;
          }
        }
      }
      else if (cmd == "print" && tree->count > 0)
      {
        std::string str = tree->recPrint(tree->root);
        str = str.substr(0, str.length() - 1);
        std::cout << str << std::endl;
      }
      else if (cmd == "clear")
      {
        tree->~QuadTree();
        std::cout << "success" << std::endl;
      }

      getline(std::cin, cmdline);
    }
  }

  return 0;
}