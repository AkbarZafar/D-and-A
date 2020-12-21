#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

class invalid_argument
{
};

class Edge
{
public:
  double weight;
  int src;
  int dest;
  Edge(double weight, int src, int dest)
  {
    this->weight = weight;
    this->src = src;
    this->dest = dest;
  }
};

class Graph
{
public:
  int n;
  double *graph;
  int edge_count;
  int *degree;

  Graph(int m)
  {
    n = m;
    graph = new double[n * n];
    degree = new int[n];

    clear_init_graph();
  }

  ~Graph()
  {
    delete[] graph;
    delete[] degree;
  }

  void init_degree()
  {
    for (int i = 0; i < n; i++)
    {
      degree[i] = 0;
    }
  }

  void init_graph()
  {
    for (int i = 0; i < (n * n); i++)
    {
      graph[i] = 0.0;
    }
  }

  void insert_node(double weight, int u, int v)
  {

    if (graph[n * u + v] == 0)
    {
      edge_count += 1;
      degree[u] += 1;
      degree[v] += 1;
    }
    graph[n * u + v] = weight;
    graph[n * v + u] = weight;
    std::cout << "success" << std::endl;
  }

  int get_degree(int u)
  {
    return degree[u];
  }

  void remove_node(int u, int v)
  {

    if (graph[n * u + v] == 0)
    {
      std::cout << "failure" << std::endl;

      return;
    }

    edge_count -= 1;
    degree[u] -= 1;
    degree[v] -= 1;
    graph[n * u + v] = 0;
    graph[n * v + u] = 0;
    std::cout << "success" << std::endl;
  }

  void clear_init_graph()
  {
    edge_count = 0;
    init_degree();
    init_graph();
  }

  void is_valid(double i)
  {
    if (i <= 0)
    {

      throw invalid_argument();
    }
  }

  void is_valid(int i)
  {
    if (i < 0 || i >= n)
    {
      throw invalid_argument();
    }
  }

  void is_valid(int i, int j)
  {
    if (i < 0 || i >= n || j < 0 || j >= n)
    {
      throw invalid_argument();
    }
  }
};

bool compare(Edge a, Edge b)
{
  return a.weight < b.weight;
}

class Disjoint
{
public:
  std::vector<Edge> get_sorted_edge(Graph *g)
  {
    int n = g->n;
    double *graph = g->graph;

    std::vector<Edge> sorted_edge;
    for (int i = 0; i < n; i++)
    {
      for (int j = i; j < n; j++)
      {
        if (g->graph[n * i + j] != 0)
        {
          sorted_edge.push_back(Edge(graph[n * i + j], i, j));
        }
      }
    }

    std::sort(sorted_edge.begin(), sorted_edge.end(), compare);
    return sorted_edge;
  }

  int parent(int a, int *disj)
  {
    if (disj[a] == a)
    {
      return a;
    }

    return parent(disj[a], disj);
  }

  double mst(Graph *g)
  {
    int *disj = new int[g->n];
    std::vector<Edge> edges = get_sorted_edge(g);
    double Tweight = 0;
    int counter = 0;
    double *graph = g->graph;
    for (int i = 0; i < g->n; i++)
    {
      disj[i] = i;
    }

    for (int i = 0; i < g->edge_count; i++)
    {
      Edge edge = edges[i];
      int a = edge.dest;
      int b = edge.src;
      if (parent(a, disj) != parent(b, disj))
      {
        counter++;
        Tweight += edge.weight;
        disj[parent(b, disj)] = parent(a, disj);
      }
    }

    delete[] disj;

    if (counter != (g->n) - 1)
    {
      return -1;
    }
    return Tweight;
  }
};

int main()
{
  std::string cmdline;
  getline(std::cin, cmdline);
  Graph *g = nullptr;
  Disjoint *d = new Disjoint();
  while (!std::cin.eof())
  {
    if (cmdline == "exit")
    {
      delete g;
      g = nullptr;
      delete d;
      d = nullptr;
      return 0;
    }
    else
    {
      std::size_t commandindex = cmdline.find(' ');

      std::string cmd = cmdline.substr(0, commandindex);
      cmdline = cmdline.substr(commandindex + 1);

      if (cmd == "n")
      {
        try
        {
          int m = std::stoi(cmdline);
          if (m <= 0)
          {
            throw invalid_argument();
          }
          g = new Graph(m);
          std::cout << "success" << std::endl;
        }
        catch (invalid_argument)
        {
          std::cout << "invalid argument" << std::endl;
        }
      }
      else if (cmd == "i")
      {
        std::size_t semi = cmdline.find(';');
        int u = std::stoi(cmdline.substr(0, semi));
        cmdline = cmdline.substr(semi + 1);
        semi = cmdline.find(';');
        int v = std::stoi(cmdline.substr(0, semi));

        double w = std::stod(cmdline.substr(semi + 1));
        try
        {
          g->is_valid(u, v);
          g->is_valid(w);
          g->insert_node(w, u, v);
        }
        catch (invalid_argument)
        {
          std::cout << "invalid argument" << std::endl;
        }
      }
      else if (cmd == "degree")
      {
        int num = std::stoi(cmdline);
        try
        {
          g->is_valid(num);
          std::cout << "degree of " << num << " is " << g->degree[num] << std::endl;
        }
        catch (invalid_argument)
        {
          std::cout << "invalid argument" << std::endl;
        }
      }
      else if (cmd == "d")
      {
        std::size_t semi = cmdline.find(';');
        int u = std::stoi(cmdline.substr(0, semi));
        cmdline = cmdline.substr(semi + 1);
        int v = std::stoi(cmdline);

        try
        {
          g->is_valid(u, v);
          g->remove_node(u, v);
        }
        catch (invalid_argument)
        {
          std::cout << "invalid argument" << std::endl;
        }
      }
      else if (cmd == "edge_count")
      {
        std::cout << "edge count is " << g->edge_count << std::endl;
      }
      else if (cmd == "clear")
      {
        g->clear_init_graph();
        std::cout << "success" << std::endl;
      }
      else if (cmd == "mst")
      {
        double w = d->mst(g);
        if (w == -1)
        {
          std::cout << "not connected" << std::endl;
        }
        else
        {
          std::cout << std::fixed << std::setprecision(2) << "mst " << w << std::endl;
        }
      }

      getline(std::cin, cmdline);
    }
  }

  return 0;
}