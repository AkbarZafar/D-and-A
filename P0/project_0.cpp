#include <iostream>
#include <cmath>

class node
{
public:
  node(int power, int coeff)
  {
    this->coeff = coeff;
    this->power = power;
  }

  void set_coeff(int coeff)
  {
    this->coeff = coeff;
  }

  int get_coeff()
  {
    return this->coeff;
  }

  void set_power(int power)
  {
    this->power = power;
  }

  int get_power()
  {
    return this->power;
  }

  void set_next(node *next)
  {
    this->next = next;
  }

  node *get_next()
  {
    return this->next;
  }

private:
  int coeff;
  int power;
  node *next;
};

class polynomial
{
  polynomial(int m, int coeff[])
  {
    if (m < 1)
      return;

    head = new node(0, coeff[0]);
    node *poly = head;
    for (int i = 1; i < m; i++)
    {
      node *new_node = new node(i, coeff[i]);
      poly->set_next(new_node);
      poly = poly->get_next();

      //delete pointer
      new_node = nullptr;
      delete new_node;
    }
    //deallocate memory
    poly = nullptr;
    delete poly;
  }

  bool get(polynomial *expected_polynomial)
  {
    //go through whole polynomial and see if each term is identical.
    node *poly = head;
    node *exp_poly = expected_polynomial->head;
    if (exp_poly == nullptr || poly == nullptr)
      return false;

    while (poly != nullptr)
    {
      exp_poly = expected_polynomial->head;
      while (poly->get_power() != exp_poly->get_power())
      {
        exp_poly = exp_poly->get_next();
        if (exp_poly == nullptr)
          return false;
      }
      if (poly->get_coeff() != exp_poly->get_coeff())
        return false;
    }
    return true;
  }

  bool eval(int x, int expected_value)
  {
    node *poly = head;
    int value = 0;
    while (poly->get_next())
    {
      value += poly->get_coeff() * pow(x, poly->get_power());
      poly = poly->get_next();
    }

    return expected_value == value;
  }

  bool add(polynomial expected_poly)
  {
    
  }

private:
  node *head;
};
//init polynomial

//evaluate polynomial

//add polynominals

//multiplying polynomial
