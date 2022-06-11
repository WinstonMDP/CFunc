class C;

class A {
public:
        C* outC() { return do_outC(); }
        virtual C* do_outC() = 0;
};

class C {
public:
        virtual A* outA() = 0;
};


class D;

class B : public A {
public:
        D* outC();
        virtual C* do_outC();
};

class D : public C {
public:
        B* outA();
};

D* B::outC() {
        return static_cast<D*>(do_outC());
}

C* B::do_outC() {
        return new D();
}

B* D::outA() {
        return new B();
}