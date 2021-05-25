#ifndef CARMODEL_H_
#define CARMODEL_H_
namespace structures
{
    class CarModel
    {
    private:
        int sales;
        int complaints;
        int grade;
        int id;
        int type;

    public:
        CarModel() = default;
        CarModel(int id, int type) : sales(0), complaints(0), grade(0), id(id), type(type) {}
        ~CarModel() = default;
        CarModel(const CarModel &model) = default;

        // Parameter functions
        int &Sales();
        int &Complaints();
        int &Grade();
        int Id();
        int Type();
        bool isBetterModel(const CarModel &model) const;
        bool isBetterSeller(const CarModel &) const;

        // Operator overload
        CarModel &operator=(const CarModel &model) = default;
        bool operator>(const CarModel &model) const;
        bool operator>=(const CarModel &model) const;
        bool operator<(const CarModel &model) const;
        bool operator<=(const CarModel &model) const;
        bool operator==(const CarModel &model) const;
    };
}

#endif