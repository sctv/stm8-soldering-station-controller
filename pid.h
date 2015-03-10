

typedef struct {
    int8_t dstate;	//last position input
    int8_t istate;	//integrator state

    int8_t imax, imin;	//integratir limits

    int8_t vmax,vmin;	//result limits

    int8_t pgain, igain, dgain;
} pid_struct;


int8_t update_pid(pid_struct *pid, int8_t error, uint8_t position);
