#ifndef TAYLOR_H
#define TAYLOR_H

#include <cmath>

/// @brief A class that holds taylor series information
class Taylor {
	private:

		/// @brief Derivatives array
		double * derivatives = NULL;

		/// @brief Size of the derivatives array
		unsigned int arrsize;

		/// @brief Corrent position, or a-value
		double position;

		/// @brief Initialise, or re-initialise, the underlying data
		///
		/// @param size The size
		/// @param a_value The position/a-value
		void Init(unsigned int size, double a_value);

	public:

		/// @brief Constructor
		///
		/// @param size The number of derivatives, not includeing the zero
		Taylor(unsigned int size);
		Taylor(unsigned int size, double init_position);
		Taylor();

		Taylor(const Taylor &other);

		/// @brief Copy operator
		///
		/// @param other Another taylor series
		///
		/// @return This
		Taylor& operator=(const Taylor& other);


		/// @brief Destructor
		~Taylor();

		/// @brief Get the derivative value
		///
		/// @param index The index
		///
		/// @return The derivatives array value
		inline double getDerivative(unsigned int index) const {
			if (index >= arrsize)
				return 0;
			return derivatives[index];
		}

		/// @brief Set a derivative value, resizing underlying array if larger than
		///
		/// @param index The index
		/// @param value The value
		void setDerivative(unsigned int index, double value);

		/// @brief Resize the derivatives array
		///
		/// @param newsize The new size
		void resize(unsigned int newsize);

		/// @brief Set the position (a-value)
		///
		/// @param npos
		inline void setPosition(double npos) {
			this->position = npos;
		}

		/// @brief Get the current position (a-value)
		///
		/// @return The position
		inline double getPosition() const {
			return this->position;
		}

		/// @brief Get the maximum derivative present in the array (i.e, the arrray size minus 1)
		///
		/// @return arrsize - 1
		inline unsigned int getSize() const {
			return this->arrsize - 1;
		}

		double Calculate(double x) const;

		double Calculate(double x, int components) const;
};

#endif
