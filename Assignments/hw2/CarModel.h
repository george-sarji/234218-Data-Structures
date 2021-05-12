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

        // Parameter functions
        int& Sales();
        int& Complaints();
        int& Grade();
        int& Id();

        // Operator overload
        bool operator>(const CarModel& model) const;
        bool operator>=(const CarModel& model) const;
        bool operator<(const CarModel& model) const;
        bool operator<=(const CarModel& model) const;
        bool operator==(const CarModel& model) const;
    };
}

#endif;