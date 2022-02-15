#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
/*
struct Image {
  double quality;
  double freshness;
  double rating;
};

struct Params {
  double a;
  double b;
  double c;
};*/

class FunctionPart {
public:
    FunctionPart( char new_operation,  double new_value) {
        operation = new_operation;
        value = new_value;
    }
    double Apply (double a) const {
        if (operation == '+') {
            return a + value;
        } else return a - value;
    }
    void Invert() {
        if (operation == '+') {
            operation = '-';
        } else  {
            operation = '+';
        }
    }
private:
    char operation;
    double value;
};

class Function {
public:
    void AddPart ( char operation,  double value) {
        opers.push_back({operation, value});
    }
    double Apply (double value) const {
        for (const FunctionPart& oper : opers) {
            value = oper.Apply(value);
        }
        return value;
    }
    void Invert() {
        for (FunctionPart& oper : opers) {
            oper.Invert();
        }
        reverse(begin(opers), end(opers));
    }
private:
    vector<FunctionPart> opers;
};
/*
Function MakeWeightFunction(const Params& params,
                            const Image& image) {
  Function function;
  function.AddPart('-', image.freshness * params.a + params.b);
  function.AddPart('+', image.rating * params.c);
  return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
  Function function = MakeWeightFunction(params, image);
  return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
                              const Image& image,
                              double weight) {
  Function function = MakeWeightFunction(params, image);
  function.Invert();
  return function.Apply(weight);
}

int main() {
  Image image = {10, 2, 6};
  Params params = {4, 2, 6};
  cout << ComputeImageWeight(params, image) << endl;
  cout << ComputeQualityByWeight(params, image, 46) << endl;
  return 0;
}*/
