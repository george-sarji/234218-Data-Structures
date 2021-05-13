#ifndef CARMODEL_H_
#define CARMODEL_H_
namespace structures
{
    class CarModel
    {
    private:
        int sales, complaints, grade, id;

    public:
        CarModel() = default;
        CarModel(int id): id(id), complaints(0), grade(0), sales(0) {}
        ~CarModel() = default;
        CarModel(const CarModel& model) = default;

        // Parameter functions
        int& Sales();
        int& Complaints();
        int& Grade();
        int& Id();

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