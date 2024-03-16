#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

class Point{
protected:
    vector<double> mCoordinates;
    double mDistance;
    friend class Point2D;
    friend class Point3D;
    friend class Point4D;
public:
    virtual void print()=0;
    virtual void calculateDistance()=0;
    virtual Point* add(Point* point){return point;}
    virtual Point* multiply(Point* point){return point;}
    double getDistance(){return mDistance;}
    void setDistance(double value){mDistance=value;}
    uint64_t getSize(){return mCoordinates.size();}
};
class Point2D: public Point{
public:
    Point2D(double a, double b){
        mCoordinates.push_back(a);
        mCoordinates.push_back(b);
    }
    Point2D(){
        mDistance=0;
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
    }
    void print() override{
        if(mCoordinates[1] < 0)
            cout << fixed << setprecision(3) << mCoordinates[0] << mCoordinates[1] << "i -> " << getDistance() << endl;
        else cout << fixed << setprecision(3) << mCoordinates[0] << "+" << mCoordinates[1] << "i -> " << getDistance() << endl;
    }
    void calculateDistance() override{
        double med= (mCoordinates[0] + mCoordinates[1]) / 2;
        if(med<0) med=0-med;
        double prod= mCoordinates[0] * mCoordinates[1];
        if(prod<0) prod=0-prod;
        mDistance=med+sqrt(prod);
    }
    Point* add(Point* point) override{
        mCoordinates[0] += point->mCoordinates[0];
        mCoordinates[1] += point->mCoordinates[1];
        return this;
    }
    Point* multiply(Point* p){
        double a, b;
        a = mCoordinates[0] * p->mCoordinates[0] - mCoordinates[1] * p->mCoordinates[1];
        b = mCoordinates[0] * p->mCoordinates[1] + p->mCoordinates[0] * mCoordinates[1];
        return new Point2D(a, b);
    }
};
class Point3D: public Point{
public:
    Point3D(double a, double b, double c){
        mCoordinates.push_back(a);
        mCoordinates.push_back(b);
        mCoordinates.push_back(c);
    }
    Point3D(){
        mDistance=0;
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
    }
    void print() override{
        if(mCoordinates[1] < 0){
            if(mCoordinates[2] < 0) cout << fixed << setprecision(3) << mCoordinates[0] << mCoordinates[1] << "i" << mCoordinates[2] << "j -> " << getDistance() << endl;
            else cout << fixed << setprecision(3) << mCoordinates[0] << mCoordinates[1] << "i" << "+" << mCoordinates[2] << "j -> " << getDistance() << endl;
        }else{
            if(mCoordinates[2] < 0) cout << fixed << setprecision(3) << mCoordinates[0] << "+" << mCoordinates[1] << "i" << mCoordinates[2] << "j -> " << getDistance() << endl;
            else cout << fixed << setprecision(3) << mCoordinates[0] << "+" << mCoordinates[1] << "i" << "+" << mCoordinates[2] << "j -> " << getDistance() << endl;
        }
    }
    void calculateDistance() override{
        double med= (mCoordinates[0] + mCoordinates[1] + mCoordinates[2]) / 3;
        if(med<0) med=0-med;
        double prod= mCoordinates[0] * mCoordinates[1] * mCoordinates[2];
        if(prod<0) prod=0-prod;
        mDistance=med+pow(prod, 1.0/3.0);
    }
    Point* add(Point* point) override{
        double a, b,c;
        if(point->mCoordinates.size()==2){
            mCoordinates[0] += point->mCoordinates[0];
            mCoordinates[1] += point->mCoordinates[1];
//            c= mCoordinates[2];
        }else{
            mCoordinates[0] += point->mCoordinates[0];
            mCoordinates[1] += point->mCoordinates[1];
            mCoordinates[2] += point->mCoordinates[2];
        }
        return this;
    }
    Point* multiply(Point *p) override{
        double a, b, c;
        if(p->mCoordinates.size()==2) {
            a = mCoordinates[0] * p->mCoordinates[0] - mCoordinates[1] * p->mCoordinates[1];
            b = mCoordinates[0] * p->mCoordinates[1] + mCoordinates[1] * p->mCoordinates[0];
            c = mCoordinates[2] * p->mCoordinates[0];
        }else{
            a=mCoordinates[0]*p->mCoordinates[0]-mCoordinates[1]*p->mCoordinates[1]-mCoordinates[2]*p->mCoordinates[2];
            b=mCoordinates[0]*p->mCoordinates[1]+mCoordinates[1]*p->mCoordinates[0];
            c=mCoordinates[0]*p->mCoordinates[2]+mCoordinates[2]*p->mCoordinates[0];
        }
        if(c==0) return new Point2D(a,b);
        return new Point3D(a,b,c);
    }
    // (a+bi+cj)(d+ei+fj)=ad+aei+afj+bdi-be+cdj-cf=   (ad-be-cf)+i(ae+bd)+j(af+cd);
    //(a+bi+cj)(d+ei)=ad+aei+bdi-be+cdj=     (ad-be)+i(ae+bd)+j(cd);
};
class Point4D: public Point{
public:
    Point4D(double a, double b, double c, double d){
        mCoordinates.push_back(a);
        mCoordinates.push_back(b);
        mCoordinates.push_back(c);
        mCoordinates.push_back(d);
    }
    Point4D(){
        mDistance=0;
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
        mCoordinates.push_back(0);
    }
    void print() override{
        if(mCoordinates[1] < 0){
            if(mCoordinates[2] < 0){
                if(mCoordinates[3] < 0) cout << fixed << setprecision(3) << mCoordinates[0] << mCoordinates[1] << "i" << mCoordinates[2] << "j" << mCoordinates[3] << "k -> " << getDistance() << endl;
                else cout << fixed << setprecision(3) << mCoordinates[0] << mCoordinates[1] << "i" << mCoordinates[2] << "j+" << mCoordinates[3] << "k -> " << getDistance() << endl;
            }
            else{
                if(mCoordinates[3] < 0) cout << fixed << setprecision(3) << mCoordinates[0] << mCoordinates[1] << "i+" << mCoordinates[2] << "j" << mCoordinates[3] << "k -> " << getDistance() << endl;
                cout << fixed << setprecision(3) << mCoordinates[0] << mCoordinates[1] << "i+" << mCoordinates[2] << "j+" << mCoordinates[3] << "k -> " << getDistance() << endl;
            }
        }else{
            if(mCoordinates[2] < 0){
                if(mCoordinates[3] < 0) cout << fixed << setprecision(3) << mCoordinates[0] << "+" << mCoordinates[1] << "i" << mCoordinates[2] << "j" << mCoordinates[3] << "k -> " << getDistance() << endl;
                else cout << fixed << setprecision(3) << mCoordinates[0] << "+" << mCoordinates[1] << "i" << mCoordinates[2] << "j+" << mCoordinates[3] << "k -> " << getDistance() << endl;
            }else{
                if(mCoordinates[3] < 0) cout << fixed << setprecision(3) << mCoordinates[0] << "+" << mCoordinates[1] << "i+" << mCoordinates[2] << "j" << mCoordinates[3] << "k -> " << getDistance() << endl;
                else cout << fixed << setprecision(3) << mCoordinates[0] << "+" << mCoordinates[1] << "i+" << mCoordinates[2] << "j+" << mCoordinates[3] << "k -> " << getDistance() << endl;
            }
        }
    }
    void calculateDistance() override{
        double med= (mCoordinates[0] + mCoordinates[1] + mCoordinates[2] + mCoordinates[3]) / 4;
        double prod=(mCoordinates[0] * mCoordinates[1] * mCoordinates[2] * mCoordinates[3]);
        if(med<0) med=0-med;
        if(prod<0) prod=0-prod;
        mDistance=med+pow(prod, 1.0/4.0);
    }
    Point* add(Point* point) override{
        if(point->mCoordinates.size()==2){
            mCoordinates[0] += point->mCoordinates[0];
            mCoordinates[1] += point->mCoordinates[1];
//            c = mCoordinates[2];
//            d = mCoordinates[3];
        }else if(point->mCoordinates.size()==3){
            mCoordinates[0] += point->mCoordinates[0];
            mCoordinates[1] += point->mCoordinates[1];
            mCoordinates[2] += point->mCoordinates[2];
//            d = mCoordinates[3];
        }else {
            mCoordinates[0] += point->mCoordinates[0];
            mCoordinates[1] += point->mCoordinates[1];
            mCoordinates[2] += point->mCoordinates[2];
            mCoordinates[3] += point->mCoordinates[3];
        }
        return this;
    }
    Point* multiply(Point *p) override{
        double a,b,c,d;
        if(p->mCoordinates.size()==4){
            a=mCoordinates[0]*p->mCoordinates[0]-mCoordinates[1]*p->mCoordinates[1]-mCoordinates[2]*p->mCoordinates[2]-mCoordinates[3]*p->mCoordinates[3];
            b=mCoordinates[0]*p->mCoordinates[1]+mCoordinates[1]*p->mCoordinates[0];
            c=mCoordinates[0]*p->mCoordinates[2]+mCoordinates[2]*p->mCoordinates[0];
            d=mCoordinates[0]*p->mCoordinates[3]+mCoordinates[3]*p->mCoordinates[0];
        }else if(p->mCoordinates.size()==3){
            a=mCoordinates[0]*p->mCoordinates[0]-mCoordinates[1]*p->mCoordinates[1]-mCoordinates[2]*p->mCoordinates[2];
            b=mCoordinates[0]*p->mCoordinates[1]+mCoordinates[1]*p->mCoordinates[0];
            c=mCoordinates[0]*p->mCoordinates[2]+mCoordinates[2]*p->mCoordinates[0];
            d=mCoordinates[3]*p->mCoordinates[0];
        }else{
            a=mCoordinates[0]*p->mCoordinates[0]-mCoordinates[1]*p->mCoordinates[1];
            b=mCoordinates[0]*p->mCoordinates[1]+mCoordinates[1]*p->mCoordinates[0];
            c=mCoordinates[2]*p->mCoordinates[0];
            d=mCoordinates[3]*p->mCoordinates[0];
        }
        if(d==0&&c!=0) return new Point3D(a,b,c);
        if(d==0&&c==0) return new Point2D(a,b);
        return new Point4D(a,b,c,d);
    }
    // (a+bi+cj+dk)(e+fi+gj+hk)=ae+afi+agj+ahk+bei-bf+cej-cg+dek-dh=
    // (ae-bf-cg-dh)+i(af+be)+j(ag+ce)+k(ah+de)

    //(a+bi+cj+dk)(e+fi+gj)=(ae-bf-cg)+i(af+be)+j(ag+ce)+k(de)
    //(a+bi+cj+dk)(e+fi)=(ae-bf)+i(af+be)+j(ce)+k(de)
};
bool cmp(Point* p1, Point* p2){
    return p1->getDistance()>p2->getDistance();
}
bool cmp_size(Point* p1, Point* p2){
    return p1->getSize()>p2->getSize();
}

int main() {
    vector<Point*> points;
    double a, b, c, d;
    while(cin>>a){
        getchar();
        cin>>b;
        if(getchar() == ';'){
            cin>>c;
            if(getchar() == ';'){
                cin>>d;
                points.push_back(new Point4D(a,b,c,d));
            }else {
                points.push_back(new Point3D(a,b,c));
            }
        }else {
            points.push_back(new Point2D(a,b));
        }
    }
    Point4D sum_4D;
    Point3D sum_3D;
    Point2D sum_2D;
    for(int i=0;i<points.size();i++){
        if(points[i]->getSize()==4)
            sum_4D.add(points[i]);
        if(points[i]->getSize()==3)
            sum_3D.add(points[i]);
        if(points[i]->getSize()==2)
            sum_2D.add(points[i]);
    }
    sum_4D.calculateDistance();
    double sum4d=sum_4D.getDistance();
    sum_3D.calculateDistance();
    double sum3d=sum_3D.getDistance();
    sum_2D.calculateDistance();
    double sum2d=sum_2D.getDistance();

    for(int i=0; i<points.size();i++){
        points[i]->calculateDistance();
    }
    vector<Point*> points_;
    for(int i=0; i<points.size();i++){
        if(points[i]->getDistance()>=sum4d&&points[i]->getSize()==4) {
            double di = points[i]->getDistance();
            points[i]=points[i]->multiply(points[i]);
            points[i]->setDistance(di);
            points_.push_back(points[i]);
        }
        if(points[i]->getDistance()>=sum3d&&points[i]->getSize()==3){
            double di = points[i]->getDistance();
            points[i]=points[i]->multiply(points[i]);
            points[i]->setDistance(di);
            points_.push_back(points[i]);
        }
        if(points[i]->getDistance()>=sum2d&&points[i]->getSize()==2){
            double di = points[i]->getDistance();
            points[i]=points[i]->multiply(points[i]);
            points[i]->setDistance(di);
            points_.push_back(points[i]);
        }
    }
    sort(points_.begin(), points_.end(), cmp);
    sort(points_.begin(), points_.end(), cmp_size);
    for(int i=0; i<points_.size();i++) points_[i]->print();
    return 0;
}