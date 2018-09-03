template <class T>
class vector3d
{
    public: 
        T x, y, z;

        vector3d()
        {
            x = 0;
            y = 0;
            z = 0;
        }

        vector3d(T x_, T y_, T z_)
        {
            x = x_;
            y = y_;
            z = z_;
        }

        inline vector3d& operator +=(const vector3d& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        inline vector3d& operator +(const vector3d& rhs)
        {
            *this += rhs;
            return *this;
        }

        inline vector3d& operator /=(const T& rhs)
        {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }

        inline vector3d& operator /(const T& rhs)
        {
            *this /= rhs;
            return *this;
        }        
};