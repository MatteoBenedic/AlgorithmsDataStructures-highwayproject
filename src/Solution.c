//Versione con diverso pian indietro

#include <stdio.h>
#include <stdlib.h>

#define PARENT(x) (x-1)/2
#define LEFT(x) 2*x+1
#define RIGHT(x) 2*x+2
#define PARK 512
#define MAXINSTR 19


typedef struct stazione{
        int dist;
        int *park;
        int lenpark;
}station;


typedef struct items{
        station staz;
        struct items* next;
}item;

typedef struct vert{
        int dist;
        int a;
        struct vert* pred;
}vrtc;

typedef struct listi{
	int val;
	struct listi* next;
}lsi;



void maxHeapify(int* a, int x, int len){
        int posmax, tmp;
        int l = LEFT(x);
        int r = RIGHT(x);
        if( l<len && a[l]>a[x])
                posmax = l;
        else
                posmax = x;
        if( r<len && a[r]>a[posmax])
                posmax = r;
        if(posmax != x){
                tmp= a[x];
                a[x] = a[posmax];
                a[posmax] = tmp;
                maxHeapify(a, posmax, len);
        }
        return;
};

int cercaAuto(int* park, int j, int aut, int lenpark){
        int i;
        if((park[j] == aut)&&(lenpark > 0))
                return j;
        else{
                if((LEFT(j) >= lenpark) || (park[j] < aut))
                        return -1;
                else{
                        i = cercaAuto(park, LEFT(j), aut, lenpark);
                        if(i == -1){
                                if(RIGHT(j) >= lenpark)
                                        return -1;
                                else
                                        i = cercaAuto(park, RIGHT(j), aut, lenpark);
                        }
                }
        }
        return i;
};

int hashSp(int i){
        int k = 1;
        for(int j = 0; j < i; j++)
                k= 2*k;
        return k-1;
};

int hashCode(int stat, int m){
        return ((stat + 17) % 4999) % m;     
};


int chooseInstr(char *s){
        
        int ch;
        if(s[0] == 'a'){
                if(s[9] == 's')
                        ch = 1;
                else
                        ch = 2;
        }else{
                if(s[7] == 'c'){
                        if(s[0] == 'd')
                                ch = 3;
                        else
                        ch = 5;
                }else
                        ch = 4;
        }
        return ch;
};



int cercaStaz(int val, item* v, int m){
        int k;
        int n = -1;
        item* p = NULL;

        k = hashCode(val, m);
        p = &v[k];

        while(p != NULL){
                if(p -> staz.dist == val){
                        n = k;
                        break;
                }else
                        p = p -> next;
        }

        return n;
};


void insert(int val, item* v, int m, int* park, int lenpark){
        int k;
        item* p = NULL;
        item* new = NULL;

        k = hashCode(val, m);
        p = &v[k];

        if(p-> staz.dist == -1){
                p -> staz.dist = val;
                p -> staz.park = park;
                p -> staz.lenpark = lenpark;
        }else{
                while(p -> next)
                        p  = p-> next;
                new = malloc(sizeof(item));
                new -> staz.dist = val;
                p -> next = new;
                new -> next = NULL;
                new -> staz.park = park;
                new -> staz.lenpark = lenpark;
        }

        return;
};



item* rifall(item* v, int dim, int nel){
        station vec[nel];
        station* tmp = NULL;
        item* tp = NULL;
        item* p = NULL;
        item* new = NULL;
        int j = 0;
        int cn = 0;
        int ls;

        while(j < nel){
                p = &v[cn];
                if(p->staz.dist !=-1){
                        ls = 0;
                        while((p != NULL)){
                                vec[j] = p -> staz;
                                j++;
                                if(ls == 0)
                                        p = p -> next;
                                else{
                                        tp = p;
                                        p = p -> next;
                                        free(tp);
                                }
                                ls++;

                        }
                }
                cn++;
        }

        free(v);
        new = malloc(dim*sizeof(item));

        for(int i=0; i<dim; i++){
                p = &new[i];
                p -> next = NULL;
                p -> staz.dist = -1;
                p -> staz.park = NULL;
                p -> staz.lenpark = 0;
        }


        for(int i = 0; i < nel; i++){
                tmp = &vec[i];
                insert(tmp->dist, new, dim, tmp->park, tmp->lenpark);
        }


        return new;
};



item* aggStaz(item* s, int* m, int* mI, int* num){      
        int val, nAuto;
        int* park;
        float lf;
        int k;
        int lenpark;

        if(scanf("%d", &val)){};

        k = cercaStaz(val, s, *m);
        if(k == -1){
                if(scanf("%d", &nAuto)){
                };
                if((park= malloc(512*sizeof(int)))){
                        for(int i=nAuto; i<512; i++)
                                park[i]= 0;
                        lenpark = nAuto;
                        for(int i=0; i<nAuto; i++)
                                if(scanf(" %d", &park[i])){};

                        for(int i= lenpark/2 -1; i>=0; i--)
                                maxHeapify(park, i, lenpark);


                }else{
                        printf("Errore alloc parcheggio");
                        return NULL;
                }

                (*num)++;
                lf = *num/(float)(*m);
                if(lf > 1.5){
                        (*mI)++;
                        *m =(int)hashSp(*mI);
                        s= rifall(s, *m, (*num)-1);
                }

                insert(val, s, *m, park, lenpark);


                printf("aggiunta");
        }
        else{
                if(scanf("%d", &nAuto)){};
                for(int i=0; i < nAuto; i++){
                        if(scanf(" %d", &val)){};
                        val = 0;
                }

                printf("non aggiunta");
        }

        if((scanf("\n"))){};
        printf("\n");
        return s;
};


item* aggAuto(item* s, int m){
        int i, l, pr;
        int val, k, car;
        int* park= NULL;
        item* p = NULL;

        if(scanf("%d", &val)){};
        if(scanf("%d", &car)){};

        k = cercaStaz(val, s, m);
        if(scanf("\n")){};
        if(k != -1){
                p = &s[k];
                while((p -> staz.dist) != val)
                        p = p -> next;
                park = p -> staz.park;
                l = p -> staz.lenpark;

                if(l<512){
                        l++;
                        park[l-1] = car;

                        i = l-1;
                        pr = PARENT(i);
                        while((i > 0) && (park[pr] < park[i])){
                                park[pr] += park[i];
                                park[i] = park[pr] - park[i];
                                park[pr] -= park[i];
                                i = pr;
                                pr = PARENT(i);
                        }

                        p -> staz.park = park;
                        p -> staz.lenpark = l;

                        printf("aggiunta");
                }else
                        printf("non aggiunta");
        }else
                printf("non aggiunta");

        printf("\n");
        return s;
};



item* demStaz(item* s, int m, int* num){

        int k, val;
        int*  mp = NULL;
        item* p = NULL;
        item* tmp = NULL;

        if(scanf("%d\n", &val)){};
        k = cercaStaz(val, s, m);


        if(k!=-1){
                p = &s[k];

                if((p -> staz.dist) == val){
                        if((p -> next)!= NULL){
                                p = p -> next;
                                mp = s[k].staz.park;
                                s[k].staz.park = NULL;
                                free(mp);
                                s[k].staz = p->staz;
                                s[k].next = p-> next;
                                free(p);

                        }else{
                                p -> staz.dist = -1;
                                p -> staz.lenpark = 0;
                                mp = p -> staz.park;
                                p -> staz.park = NULL;
                                free(mp);
                        }
                }else{
                        do{
                                tmp = p;
                                p = p -> next;
                        }while((p -> staz.dist) != val);

                        if(p -> next){
                                mp = p -> staz.park;
                                p -> staz.park = NULL;
                                tmp -> next = p -> next;
                                free(mp);
                                free(p);
                        }else{
                                tmp -> next = NULL;
                                mp = p -> staz.park;
                                p -> staz.park = NULL;
                                free(mp);
                                free(p);
                        }
                }
                (*num)--;
                printf("demolita");
        }else
                printf("non demolita");

        printf("\n");

        return s;
};


item* rotAuto(item* s, int m){
        int val, k, car, i, l, tmp;
        item* p = NULL;
        int* park = NULL;

        if(scanf("%d", &val)){};
        if(scanf("%d\n", &car)){};
        k = cercaStaz(val, s, m);

        if(k != -1){
                p = &s[k];

                while((p -> staz.dist)!= val)
                        p = p -> next;

                park = p -> staz.park;
                l = p -> staz.lenpark;
                if(park){
                        i = cercaAuto(park, 0, car, l);
                        if(i == -1)
                                printf("non rottamata");
                        else{
                                park[i] = park[l-1];
                                l--;

                                if(park[i] > park[PARENT(i)]){
                                        do{
                                                tmp = park[i];
                                                park[i] = park[PARENT(i)];
                                                park[PARENT(i)] = tmp;
                                                i = PARENT(i);
                                        }while((park[i] > park[PARENT(i)]) && (i > 0));
                                }else
                                        maxHeapify(park, i, l);

                                p -> staz.lenpark = l;
                                printf("rottamata");
                        }
                }else
                        printf("non rottamata");

                
        }else
                printf("non rottamata");

        printf("\n");
        return s;
};


int part(vrtc* v, int low, int hig){
        int pv, i, j;
        vrtc tmp;
        pv = v[low].dist;
        i = low-1;
        j = hig+1;
        while(1){
                do{
                        i++;
                }while(v[i].dist < pv);

                do{
                        j--;
                }while(v[j].dist > pv);

                if(i<j){
                        tmp = v[i];
                        v[i] = v[j];
                        v[j] = tmp;
                }else
                        return j;
        }
}

void qkSort(vrtc* v, int low, int hig){
        int p;
        if(low < hig){
                p = part(v, low, hig);
                qkSort(v, low, p);
                qkSort(v, p+1, hig);
        }
        return;
};


void printPath(vrtc* p, int s){
        if(p->dist == s)
                printf("%d", p->dist);
        else{
                printPath(p->pred, s);
                printf(" ");
                printf("%d", p->dist);
        }

        return;
};

void pianPerc(item* s, int m){
        int par, fin, n, lli;
        int j, k;
        vrtc* q = NULL;
        int st;
        vrtc* f = NULL;
        int* park= NULL;
        vrtc* list= NULL;
        item* p= NULL;
        lli = 16;
        n = 0;
	int go = 1;
	int pos;
	int prd, lp, nxprd;
        
        if(scanf("%d ", &par)){};
        if(scanf("%d ", &fin)){};

        if(par < fin){
                
                if((list = malloc(lli*sizeof(vrtc)))){
                        for(int i = 0; i < m; i++){
                                p = &s[i];
                                while((p) && (p->staz.dist != -1)){
                                        if((p->staz.dist <= fin) && (p->staz.dist >= par)){
                                                n++;
                                                if(n > lli){
                                                        lli=lli*2;
                                                        list = realloc(list, lli*sizeof(vrtc));
                                                }
                                                q = &list[n-1];
                                                q->dist = p->staz.dist;
                                                if( p -> staz.lenpark > 0){
                                                        park = p->staz.park;
                                                        q-> a = park[0];
                                                }else
                                                        q-> a = 0;
                                                q-> pred = NULL;
                                        }
                                        p = p -> next;
                                }
                        }
                        list = realloc(list, n*sizeof(vrtc));


                        qkSort(list, 0, n-1);

                        for(int i = 0; i<n; i++){
                                k  = list[i].dist + list[i].a;
                                if((list[i+1].dist > k) && (list[i+1].pred == NULL)){
                                        printf("nessun percorso\n");
                                        free(list);
                                        return;
                                }
                                if(list[n-1].dist <=  k){
                                        list[n-1].pred = &list[i];
                                        break;
                                }else{
                                        j = i+1;
                                        while(list[j].dist <=  k){
                                                if(list[j].pred == NULL)
                                                        list[j].pred = &list[i];
                                                j++;
                                        }
                                }
                        }

                        st = list[0].dist;
                        f = &list[n-1];
                        printPath(f, st);
                        printf("\n");


                        free(list);
                }
        }else{
                if(par > fin){
                        if((list = malloc(lli*sizeof(vrtc)))){
                                for(int i = 0; i < m; i++){
                                        p = &s[i];
                                        while((p) && (p->staz.dist != -1)){
                                                if((p->staz.dist >= fin) && (p->staz.dist <= par)){
                                                        n++;
                                                        if(n > lli){
                                                                lli =lli*2;
                                                                list = realloc(list, lli*sizeof(vrtc));
                                                        }
                                                        q = &list[n-1];
                                                        q->dist = p->staz.dist;
                                                        if(p->staz.lenpark > 0){
                                                                park = p->staz.park;
                                                                q-> a = park[0];
                                                        }else
                                                                q-> a = 0;
                                                        q-> pred = NULL;
                                                }
                                                p = p -> next;
                                        }
                                }
                                list = realloc(list, n*sizeof(vrtc));


                                qkSort(list, 0, n-1);
				
				lp = n-1;
				prd = n-1;
				while(go){
					pos = lp;
					nxprd = lp;
					while(pos <= prd){
						k = list[pos].dist - list[pos].a;
						
						if(list[0].dist >= k){
							list[0].pred= &list[pos];
							go = 0;
							break;
						}
						
						j = lp-1;
						while(list[j].dist >= k){
							list[j].pred = &list[pos];
							lp = j;
							j--;
						}
						
						pos++;
					}

					if((lp == nxprd) && (go == 1)){
						printf("nessun percorso\n");
						free(list);
						return;
					}

					prd = nxprd;
				}
				
			       	//METODO CON CODA	
				/*enq(&head, &tail, n-1);

				while(go){
					pos = deq(&head);
					if(pos == -1){
						libercoda(head);
						free(list);
						printf("nessun percorso\n");
						return;
					}
					
					k= list[pos].dist - list[pos].a;
					if(list[0].dist >= k){
						list[0].pred = &list[pos];
						break;
					}
					
					j = pos-1;
					while((list[j].dist >= k) && (list[j].pred!=NULL)){
						j--;
					}
					
					pk = j;
					while(list[j].dist >= k){
						list[j].pred = &list[pos];
						j--;
					}
					for(int i = j+1; i<= pk; i++)
						enq(&head, &tail, i);
				}*/
				
                     
                                st = list[n-1].dist;
                                f = &list[0];
                                printPath(f, st);
                                printf("\n");			
				
                                free(list);
                        }
                }else
                        printf("%d\n", par);
        }

        return;
};


int main(int argc, char* argv[])
{
        char *instr, t;
        int go = 1;
        int cnt, cn, j;
        int ls;
        int swt;

        item* stazioni;
        item* p = NULL;
        item* tp = NULL;
        int* mp = NULL;
        int m, mI, nelem;

        mI = 3;
        m = (int)hashSp(mI);
        nelem = 0;
        stazioni = malloc(m*sizeof(item));

        for(int i=0; i<m; i++){
                p = &stazioni[i];
                p -> next = NULL;
                p -> staz.dist = -1;
                p -> staz.lenpark = 0;
                p -> staz.park = NULL;
        }
        

        while(go){
                if((instr = calloc(MAXINSTR,sizeof(char)))){
                        cnt = 0;
                        while (1) {
                                if(scanf("%c", &t)){};
                                if ( (t == '\n')  || (t== ' ') ) break;
                                instr[cnt] = t;
                                cnt++;
                        }
                        instr[cnt] = '\0';

                        instr = realloc(instr, (cnt+1)*sizeof(char));

                        if(cnt == 0){
                                go = 0;
                                free(instr);
                                break;
                        }

                        swt = chooseInstr(instr);
                        free(instr);
                        switch(swt){
                                case 1:
                                        stazioni = aggStaz(stazioni, &m, &mI, &nelem);
                                        break;
                                case 2:
                                        stazioni = aggAuto(stazioni, m);
                                        break;
                                case 3:
                                        stazioni = demStaz(stazioni, m, &nelem);
                                        break;
                                case 4:
                                        stazioni = rotAuto(stazioni, m);
                                        break;
                                case 5:
                                        pianPerc(stazioni, m);
                                        break;
                        }
                }
        }

        j = 0;
        cn = 0;
        while(j < nelem){
                p = &stazioni[cn];
                if(p->staz.dist !=-1){
                        ls = 0;
                        while((p != NULL)){
                                j++;

                                mp = p ->staz.park;
                                p -> staz.park = NULL;
                                free(mp);

                                if(ls == 0){
                                        p = p -> next;
                                }else{
                                        tp = p;
                                        p = p -> next;
                                        free(tp);
                                }
                                ls++;
                        }
                }
                cn++;
        }

        free(stazioni);


        return 0;
}
								
