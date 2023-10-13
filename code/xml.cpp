#include "xml.hpp"

namespace bkr
{
    std::vector<int> getKeyRange(int from = 0, int to = 128)
    {
        std::vector<int> key_range;
        for (int i = from; i < to; ++i)
        {
            key_range.push_back(i);
        };
        return key_range;
    }
    std::vector<double> getKeyWeigths(int n = 128, double mean = 60, double stddev = 6)
    {
        (n > 0) || (n = 0);
        (n <= 128) || (n = 128);
        std::vector<double> weights;
        auto normal = [mean, stddev](double x)
        {
            double coeff = 1.0 / (sqrt(2*M_PI) * stddev);
            double expo = -0.5 * pow((x - mean) / stddev, 2);
            return coeff*exp(expo);
        };
        for (double i = 0; i < n; i++) {
            double weight = normal(i);
            weights.push_back(weight);
        }
        return weights;
    }
    std::vector<int> getRandomKeys(int n, int from = 0, int to = 128, double mean = 60, double stddev = 32)
    {
        (n > 0) || (n = 0);
        (n <= 128) || (n = 128);
        std::vector<int> random_reys;
        std::vector<int> key_range = getKeyRange(from, to);
        std::vector<double> weights = getKeyWeigths(to - from, mean, stddev);
        for (int i = 0; i < n; i++) {
            std::discrete_distribution<int> discreteDistribution(weights.begin(), weights.end());
            int idx = discreteDistribution(rng);
            random_reys.push_back(key_range[idx]);
            key_range.erase(key_range.begin() + idx);
            weights.erase(weights.begin() + idx);
        };
        std::sort(random_reys.begin(), random_reys.end());
        return random_reys;
    }
 
    std::string to_string(int value)
    {
        return std::to_string(value);
    }

    std::string to_string(const char* value)
    {
        return std::string(value);
    }

    std::string to_string(const std::string& value)
    {
        return value;
    }

    std::string to_string(const bool value)
    {
        return to_string((int)value);
    }

    template<typename T>
    std::string to_string(const T& value)
    {
        return std::to_string(value);
    }

    std::string to_string(const Params& p)
    {
        if (std::is_same<decltype(p.i_val), int>::value)
        {
            return to_string(p.i_val);
        }
        else if (std::is_same<decltype(p.d_val), double>::value)
        {
            return to_string(p.d_val);
        }
        else if (std::is_same<decltype(p.b_val), bool>::value)
        {
            return to_string(p.b_val);
        }
        else if (std::is_same<decltype(p.s_val), const char*>::value)
        {
            return to_string(p.s_val);
        }
    }

    std::string fl2lc(std::string str)
    {
        for (char& c : str)
        {
            c = std::tolower(c);
            break;
        }
        return str;
    }

    std::string repeat(const char* str, int n)
    {
        std::string result;
        for (int i = 0; i < n; i++) {
            result += str;
        }
        return result;
    };
};