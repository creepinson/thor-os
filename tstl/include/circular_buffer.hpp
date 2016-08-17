//=======================================================================
// Copyright Baptiste Wicht 2013-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

/*!
 * \brief A circular buffer of maximum size S
 *
 * In a circular buffer, push are done on one side of the queue and
 * pop on the other side (FIFO)
 */
template<typename T, size_t S>
struct circular_buffer {
private:
    static constexpr const size_t Size = S + 1;

    T buffer[Size];

    volatile size_t start;
    volatile size_t end;

public:
    /*!
     * \brief Construct a new circular_buffer
     */
    circular_buffer() : start(0), end(0) {
        //Nothing to init
    }

    /*!
     * \brief Returns true if the buffer is full
     */
    bool full() const {
        return (end + 1) % Size == start;
    }

    /*!
     * \brief Returns true if the buffer is empty
     */
    bool empty() const {
        return end == start;
    }

    /*!
     * \brief Push the given value to the buffer
     * \param value The value
     */
    bool push(T value){
        if(full()){
            return false;
        } else {
            buffer[end] = value;
            end = (end + 1) % Size;

            return true;
        }
    }

    /*!
     * \brief Returns the value at the top of the buffer
     */
    T top() const {
        return buffer[start];
    }

    /*!
     * \brief Removes and returns the value at the top of the buffer
     */
    T pop(){
        auto value = buffer[start];
        start = (start + 1) % Size;
        return value;
    }

    /*!
     * \brief Removes the last element that was pushed
     *
     * This should only be used if the buffer is used by a single
     * thread.
     */
    void pop_last(){
        if(end == 0){
            end = Size - 1;
        } else {
            --end;
        }
    }
};

#endif
