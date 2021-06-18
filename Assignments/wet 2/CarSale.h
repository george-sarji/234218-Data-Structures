#ifndef CARSALE_H
#define CARSALE_H


namespace structures
{
    class CarSale
    {
        private:
            int typeId, sales;

        public:
            CarSale(int typeID, int sales) : typeId(typeID), sales(sales) {}
            CarSale(const CarSale& carType) = default;
            ~CarSale() = default;
            CarSale& operator=(const CarSale& carType) = default;

            bool operator<(const CarSale& carType) const;
            bool operator<=(const CarSale& carType) const;
            bool operator>(const CarSale& carType) const;
            bool operator>=(const CarSale& carType) const;
            bool operator==(const CarSale& carType) const;

            int getTypeID() const;
            int getSales() const;

            void setTypeID(int newID);
            void setSales(int sales);
    };
}


#endif //CARSALE_H
