class Temporizador{
private:
    clock_t startTime;
public:
    Temporizador();
    void iniciarTemporizador();
    long double getTimeInSec();

};
