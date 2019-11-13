#include "api_robot.h"
//#define MINDIFF 2.2250738585072014e-308   // smallest positive double
#define MINDIFF 2.25e-308                   // use for convergence check

float raiz_quadrada(float square){
    float root=square/3, last, diff=1;
    if (square <= 0) return 0;
    do {
        last = root;
        root = (root + square / root) / 2;
        diff = root - last;
    } while (diff > MINDIFF || diff < -MINDIFF);
    return root;
}

int arccosseno100(float cosseno){
    cosseno = cosseno * 100;
    int arccos = 0;
    if(cosseno < 60){
        arccos = -0.6*cosseno + 90;
    }else if(cosseno < 90){
        arccos = -0.9*(cosseno-60)+54;
    }else if(cosseno < 99){
        arccos = -2*(cosseno-90)+27;
    }else if(cosseno <= 100){
        arccos = -9*(cosseno-99)+9;
    }
    return arccos;
}

int amigoProx(){
    int tamanho = sizeof(friends_locations) / sizeof(friends_locations[0]);
    Vector3 posAtual;
    int vetX, vetZ, dist;
    for (int i = 0; i < tamanho; i++){
        get_current_GPS_position(&posAtual);
        vetX = (friends_locations[i].x - posAtual.x);
        vetZ = (friends_locations[i].z - posAtual.z);
        dist = raiz_quadrada((vetX*vetX) + (vetZ*vetZ));
        if(dist <= 5){
            return 1;
        }
    }
    return 0;
}

int inimigoProx(){
    int tamanho = sizeof(dangerous_locations) / sizeof(dangerous_locations[0]);
    Vector3 posAtual;
    int vetX, vetZ, dist;
    for (int i = 0; i < tamanho; i++){
        get_current_GPS_position(&posAtual);
        vetX = (dangerous_locations[i].x - posAtual.x);
        vetZ = (dangerous_locations[i].z - posAtual.z);
        dist = raiz_quadrada((vetX*vetX) + (vetZ*vetZ));
        if(dist <= 12){
            return 1;
        }
    }
    return 0;
}

void vira(int grau){
	Vector3 atual;
	Vector3 guarda;
	get_gyro_angles(&guarda);
	float dest = (guarda.y+grau)%360;
	if(dest<0){
		dest = 360 + dest;
	}
    print_num(guarda.y);
    print_num(grau);
    print_num(dest);
    get_gyro_angles(&atual);
	if(atual.y < dest){
		while(atual.y != dest){
				set_torque(15, -15);
                // print_num(2);
				get_gyro_angles(&atual);
				// print_num(atual->y);
			}
	}else{
		while(atual.y != dest){
				set_torque(-15, 15);
                // print_num(3);
				get_gyro_angles(&atual);
				// print_num(atual->y);
			}
	}
    print_num(atual.y);
	set_torque(0, 0);
	return;

}

void viraPara(int grau){
	Vector3 atual;
	get_gyro_angles(&atual);
	if(atual.y < grau){
		while(atual.y < grau){
				set_torque(15, -15);
				get_gyro_angles(&atual);
				// print_num(atual->y);
			}
	}else{
		while(atual.y > grau){
				set_torque(-15, 15);
				get_gyro_angles(&atual);
				// print_num(atual->y);
			}
	}
    print_num(atual.y);
	set_torque(0, 0);
	return;

}



int maisPerto(int tamanho, int *visitados, int num_visitados){
    int novo;
    int menor = 2147483647;
    int menor_val = 0;
    for(int i=0; i < tamanho; i++){
        int val = 1;
        for(int j=0; j < num_visitados; j++){
            if(visitados[j] == i){
                val = 0;
            }
        }
        if(val){
            novo = (friends_locations[i].z*friends_locations[i].z)+(friends_locations[i].z*friends_locations[i].z);
            if(novo<menor){
                menor_val = i;
                menor = novo;
            }
        }
    }
    if(menor == 2147483647){
        return tamanho;
    }
    return menor_val;
}


void alinha(int x, int z){
	Vector3 posAtual;
	get_current_GPS_position(&posAtual);
    int vetX = (x - posAtual.x);
	int vetZ = (z - posAtual.z);
    float modulo = raiz_quadrada((vetX*vetX)+(vetZ*vetZ));
    float cosseno = (vetX/(modulo));
    int angulo;
    Vector3 ang;
    get_gyro_angles(&ang);
    if(cosseno < 0){
        angulo = 180 - arccosseno100((-cosseno));
    }else{
        angulo = arccosseno100(cosseno);
    }
    //angulo


    // print_num(angulo);
    //
    if(vetZ < 0){
        angulo = 360 - angulo;
    }
    angulo = ang.y - angulo;
    vira(angulo);

	return;

}



void montanha(){
	int leitura;
	leitura = get_us_distance();
	int direita, esquerda;
	Vector3 atual;
	get_gyro_angles(&atual);
	if(leitura != -1){
		vira(10);
		direita = get_us_distance();
		vira(-20);
		esquerda = get_us_distance();
		if(esquerda > direita){
			vira(20);
		}
		print_num(leitura);
	}
	set_torque(20,20);
	return;
}


int main(){
	int k = 0;

	// const char* a = "-";
	// const char *b = "\n";
	int tamanho = sizeof(friends_locations) / sizeof(friends_locations[0]);
    // viraPara(0);
    // while(k < 10000000)
    // k++;
	int i = 0;
	// alinha(friends_locations[i].x, friends_locations[i].z);
    vira(122);


	print_num(1);
	while(1);
	return 0;
}
