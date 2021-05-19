#ifndef CARMODEL_H_
#define CARMODEL_H_
namespace structures
{
    class CarModel
    {
    private:
        int sales, complaints, grade, id, type;

    public:
        CarModel() = default;
        CarModel(int id, int type): id(id), complaints(0), grade(0), sales(0), type(type) {}
        ~CarModel() = default;
        CarModel(const CarModel& model) = default;

        // Parameter functions
        int& Sales();
        int& Complaints();
        int& Grade();
        int& Id();
        bool isBetterModel(const CarModel& model) const;
        bool isBetterSeller(const CarModel&) const;

        // Operator overload
        CarModel& operator=(const CarModel& model) = default;
        bool operator>(const CarModel& model) const;
        bool operator>=(const CarModel& model) const;
        bool operator<(const CarModel& model) const;
        bool operator<=(const CarModel& model) const;
        bool operator==(const CarModel& model) const;
    };
}

#endif