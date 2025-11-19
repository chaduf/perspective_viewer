#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Perspective::core::mtools {
    template<int nr_rows, int nr_cols, typename T, glm::qualifier Q>
    bool epsilonEqual(const glm::mat<nr_rows, nr_cols, T, Q>& m1, const glm::mat<nr_rows, nr_cols, T, Q>& m2, float eps = 1e-6f) {
        for (unsigned int i = 0; i < nr_rows; ++i) {
            for (unsigned int j = 0; j < nr_cols; ++j) {
                if (!glm::epsilonEqual(m1[i][j], m2[i][j], eps)) {
                    return false;
                }
            }
        }
        return true;
    }

    template<typename T, glm::qualifier Q>
    bool epsilonEqual(const glm::qua<T, Q>& q1, const glm::qua<T, Q>& q2, T eps = 1e-6f) {
        T dot = glm::dot(q1, q2);
        return std::abs(std::abs(dot) - 1.0f) <= eps;
    }
} // namespace Perspective::core::mtools