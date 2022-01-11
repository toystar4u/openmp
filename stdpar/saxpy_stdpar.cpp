#include <vector>
#include <algorithm>
#include <execution>
#include <cmath>

int main()
{
    float alpha = 2.0;
    long n = 1UL << 30;

    std::vector<float> x(n);
    std::vector<float> y(n);
    
    std::fill(x.begin(), x.end(), 1.0);
    std::fill(y.begin(), y.end(), 1.0);

    std::transform(std::execution::par_unseq, x.begin(), x.end(),   // in
                                        y.begin(),              // in
                                        y.begin(),              // out
    [=](float xi, float yi) {
        return alpha * xi + yi;
    });    

    return 0;
}
