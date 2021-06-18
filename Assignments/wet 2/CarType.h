#ifndef CARTYPE_H
#define CARTYPE_H


namespace structures
{
    class CarType
    {
        private:
            int typeID, sales;

        public:
            CarType(int typeID, int sales = 0) : typeID(typeID), sales(sales) {}
            CarType(const CarType& carType) = default;
            ~CarType() = default;
            CarType& operator=(const CarType& carType) = default;

            bool operator<(const CarType& carType) const;
            bool operator<=(const CarType& carType) const;
            bool operator>(const CarType& carType) const;
            bool operator>=(const CarType& carType) const;
            bool operator==(const CarType& carType) const;

            int getTypeID() const;
            int getSales() const;

            void setTypeID(int newID);
            void setSales(int sales);

    };
}

#endif //CARTYPE_H
