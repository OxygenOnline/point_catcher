extern const int column, row;

// ------------------------------------------------------------------------------------------- //

class Coordinates
{
    int x_;
    int y_;

  public:
    Coordinates(int first, int second)
    {
      if (first < 0)
      {
        x_ = column - 1;
      }
      else if (first >= column)
      {
        x_ = 0;
      }
      else
      {
        x_ = first;
      }

      if (second < 0)
      {
        y_ = 0;
      }
      else if (second >= row)
      {
        y_ = row - 1;
      }
      else
      {
        y_ = second;
      }
    }

    Coordinates()
    {
      x_ = 0;
      y_ = 0;
    }

    const int &x() const {
      return x_;
    }
    const int &y() const {
      return y_;
    }

    bool operator==(Coordinates const &obj)
    {
      return (x_ == obj.x() && y_ == obj.y());
    }

    Coordinates operator=(Coordinates const &obj)
    {
      if (*this == obj)
      {
        return *this;
      }

      x_ = obj.x();
      y_ = obj.y();
      return *this;
    }
};

// ------------------------------------------------------------------------------------------- //
