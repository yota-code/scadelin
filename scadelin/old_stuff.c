int matrix__init__(matrix_T * self, size_t row_n, size_t col_n) {

        memset(self, 0, sizeof(matrix_T));

        self->row_n = row_n;
        self->col_n = col_n;

}
int matrix_mul(matrix_T * result, matrix_T * a, matrix_T * b) {

        if(a->col_n == b->row_n){
        for (size_t i=0 ; i < a->row_n ; i++) {
                for (size_t j=0 ; j < b->col_n ; j++) {
                        result->data[i][j] = 0;
                        for (size_t k=0 ; k < a->row_n ; k++){
                                result->data[i][j]=result->data[i][j] + a->data[i][k]*b->data[k][j] ;
                        }
                }

        }
        return 1;
        }
        return 0;
}
int matrix_Trans(matrix_T * result, matrix_T * a) {


        for (size_t i=0 ; i < a->row_n ; i++) {
                for (size_t j=0 ; j < a->col_n ; j++) {
                                result->data[i][j]=a->data[j][i];
                }

        }

}
int matrix_add(matrix_T * result, matrix_T * a,matrix_T * b,float x,float y) {


        for (size_t i=0 ; i < a->row_n ; i++) {
                for (size_t j=0 ; j < a->col_n ; j++) {
                                result->data[i][j]=x*a->data[i][j]+y*b->data[i][j];
                }

        }

}
int matrix_print(matrix_T * self) {
        for (size_t i=0 ; i < self->row_n ; i++) {
                for (size_t j=0 ; j < self->col_n ; j++) {
                        printf("%f ", self->data[i][j]);
                }
                printf("\n");
        }
}
int cholesky(matrix_T * r, matrix_T * P) {
//https://algowiki-project.org/en/Cholesky_decomposition
float s = 0;
float tmp =0;
for (size_t j=0 ; j < P->col_n ; j++) {
        for (size_t i=0 ; i < P->row_n ; i++) {
                r->data[i][j]=P->data[i][j];
        }
}
 printf("Pr : %f %f %f %f \n", r->data[0][0],r->data[1][0],r->data[0][1],r->data[1][1]);
for (size_t i = 0; i < r->col_n; i++){
        for(size_t j=0;j < r->col_n;j++){
                s = r->data[i][j];
                if(i>0){
                        for(size_t k=0;k <i;k++){
                                s=s-r->data[i][k]*r->data[j][k];
                        }
                }
                if(i==j){
                        r->data[i][i]=sqrt(s);
                }
                else{
                        r->data[j][i]=s/r->data[i][i];
                }
        }
}
for (size_t i = 0; i < r->row_n; i++){
        for(size_t j=0;j < r->col_n;j++){
                if(j>i){
                        r->data[i][j]=0;
                }
        }
}
printf("Ur : %f %f %f %f \n", r->data[0][0],r->data[1][0],r->data[0][1],r->data[1][1]);
}
int matrix_Inv_Chol(matrix_T * result, matrix_T * P) {
        matrix_T U ;
        float s;
        float tmp;
        matrix__init__(& U, P->row_n, P->col_n);

        cholesky(& U,  P);
        /*
        Matrix Inversion using Cholesky Decomposition
        Finds the inverse of the matrix X, given its (lower triangular) Cholesky
        Decomposition; i.e. X = LL', according to the paper 'Matrix Inversion
        Using Cholesky Decomposition', Aravindh Krishnamoorthy, Deepak Menon,
        */
        printf("U : %f %f %f %f \n", U.data[0][0],U.data[0][1],U.data[1][0],U.data[1][1]);

        if(U.row_n >1){
        for (size_t j = U.row_n  ; j-- >0;) {
                for (size_t i=j+1 ; i-- >0 ;) {
                        if(i==j){
                                if(U.data[j][i]>=0){tmp = max(0.000001,U.data[j][i]);}
                                else{tmp = min(-0.000001,U.data[j][i]);}
                                s=1/tmp;//div
                                }
                        else
                                {s=0;}
                        result->data[i][j]=s;
                        if(i<U.row_n-1){
                        for (size_t k=i+1 ; k< U.row_n  ; k++) {
                                result->data[i][j]=result->data[i][j]-U.data[k][i]*result->data[k][j];
                        }
                        }
                        if(U.data[i][i]>=0){tmp = max(0.000001,U.data[i][i]);}
                                else{tmp = min(-0.000001,U.data[i][i]);}
                        result->data[i][j]=result->data[i][j]/tmp;//div
                        result->data[j][i]=result->data[i][j];
                }

        }
        }
        else{
                if(U.data[0][0]>=0){tmp = max(0.000001,U.data[0][0]);}
                else{tmp = min(-0.000001,U.data[0][0]);}
                result->data[0][0]=1/tmp;//div
                }
}

int kalman_prediction(matrix_T * result, matrix_T * P,matrix_T * F,matrix_T * Q) {
        matrix_T FP ;
        matrix_T FPFT ;
        matrix_T FT ;

        matrix__init__(& FP, F->row_n, P->col_n);
        matrix__init__(& FPFT, F->row_n, F->row_n);
        matrix__init__(& FT, F->col_n, F->row_n);

        matrix_mul(&FP, F, P);
        matrix_Trans(& FT,F);
        matrix_mul(&FPFT, &FP, & FT);
        matrix_add(result,&FPFT,Q,1.0,1.0);
        printf("Q : %f %f %f %f \n", Q->data[0][0],Q->data[1][0],Q->data[0][1],Q->data[1][1]);
        printf("FPFT : %f %f %f %f \n", FPFT.data[0][0],FPFT.data[1][0],FPFT.data[0][1],FPFT.data[1][1]);
}
int kalman_update(matrix_T * X,matrix_T * P,matrix_T * H,matrix_T * R,matrix_T * Inov) {
        matrix_T K ;
        matrix_T HT ;
        matrix_T PHT ;
        matrix_T HPHTR ; // H*P*H'+R
        matrix_T invHPHTR ; // H*P*H'+R
        matrix_T I ;
        matrix_T KH ;
        matrix_T IKH ;//I-K*H
        matrix_T Ptmp ;
        matrix_T Xtmp ;
        matrix_T KInov ;
        matrix__init__(& K, X->row_n, Inov->row_n);
        matrix__init__(& HT, H->col_n, H->row_n);
        matrix__init__(& PHT, P->row_n, H->row_n);
        matrix__init__(& HPHTR, H->row_n, H->row_n);
        matrix__init__(& invHPHTR, Inov->row_n, Inov->row_n);
        matrix__init__(& I, P->row_n, P->col_n);
        for(size_t j =0;j<P->row_n;j++){
                I.data[j][j]=1;
        }
        matrix__init__(& KH, X->row_n, H->col_n);
        matrix__init__(& IKH, P->row_n, P->col_n);
        Ptmp.row_n = P->row_n;
        Ptmp.col_n = P->col_n;
        for(size_t k =0;k<P->row_n;k++){
                for(size_t j =0;j<P->col_n;j++){
                        Ptmp.data[k][j]=P->data[k][j];
                }
        }
        Xtmp.row_n = X->row_n;
        Xtmp.col_n = X->col_n;
        for(size_t k =0;k<X->row_n;k++){
                for(size_t j =0;j<X->col_n;j++){
                        Xtmp.data[k][j]=X->data[k][j];
                }
        }
        matrix__init__(& KInov, X->row_n, Inov->col_n);


        //K= P*H'/(H*P*H'+R)
        kalman_prediction(& HPHTR,P,H,R);
        printf("HPHTR : %f %f %f %f \n", HPHTR.data[0][0],HPHTR.data[1][0],HPHTR.data[0][1],HPHTR.data[1][1]);
        matrix_Inv_Chol(& invHPHTR,& HPHTR);
        printf("invHPHTR : %f %f %f %f \n", invHPHTR.data[0][0],invHPHTR.data[1][0],invHPHTR.data[0][1],invHPHTR.data[1][1]);
        matrix_Trans(& HT,H);
        matrix_mul(&PHT, P, &HT);
        matrix_mul(&K, &PHT, &invHPHTR);
        printf("K : %f %f %f %f \n", K.data[0][0],K.data[0][1],K.data[0][1],K.data[1][1]);

        //P = (I-K*H)*P
        matrix_mul(&KH, &K, H);
        matrix_add(&IKH,&I,&KH,1.0,-1.0);
        matrix_mul(P, &IKH,& Ptmp);

        //X = X+K*I
        matrix_mul(&KInov, &K,Inov);
        matrix_add(X,&Xtmp,&KInov,1.0,1.0);

}



/*
int matrix_Low_Inv(matrix_T * result, matrix_T * L) {
        if (L->col_n != result->col_n) {printf("error Low_Inv 5\n");return 0;}
        if (L->row_n != result->row_n) {printf("error Low_Inv 4\n");return 0;}
        if (L->row_n != L->col_n) {printf("error Low_Inv 3\n");return 0;}
        for (size_t j=0 ; j < L->col_n ; j++) {
        if(L->data[j][j] < 1e-6 & L->data[j][j] > -1e-6) {printf("error Low_Inv 2\n");return 0;}
                for (size_t i=0 ; i < L->row_n ; i++) {
                        if(j>i & L->data[i][j] != 0) {printf("error Low_Inv 1\n");return 0;}
                }
        }

        for (size_t j=0 ; j < L->col_n ; j++) {
                for (size_t i=0 ; i < L->row_n ; i++) {
                            result->data[i][j]= 0;
                                if(j<=i){
                                        if (i == j){
                                        result->data[i][j]= 1;
                                        }
                                        if( i > 0){
                                                for (size_t k=0 ; k <= i-1 ; k++){
                                                result->data[i][j]= result->data[i][j]- L->data[i][k]*result->data[k][j];
                                                }
                                        }
                                        result->data[i][j]= result->data[i][j]/L->data[i][i];
                                }
                }

        }

        return 1;

}
*/


//gcc -std=c99 -lm -o a.out matrix.c && ./a.out


int main(int argc, char * argv[]) {
        float xmes = 0;
        float vmes = 0;
    float gam = 0;
        FILE* fichier = NULL;
        FILE* Mesures = NULL;

        matrix_T a = {3, 3, {{1, 0, 0}, {0, 1, 0}, {1, 1, 1}}};
        matrix_T b = {3, 3, {{1, 2, 0}, {0, 1, 2}, {0, 0, 1}}};
        matrix_T P = {3, 3, {{1, 1, 0}, {1, 2, 0}, {0, 0, 3}}};
        matrix_T L = {3, 3, {{1, 4, 0}, {4, 2, 4}, {0, 4, 3}}};
        matrix_T LT = {3, 3, {{1, 4, 0}, {4, 2, 4}, {0, 4, 3}}};
        matrix_T LLT = {3, 3, {{1, 4, 0}, {4, 2, 4}, {0, 4, 3}}};
        matrix_T invL = {3, 3, {{1, 4, 0}, {4, 2, 4}, {0, 4, 3}}};
        matrix_T invLT = {3, 3, {{1, 4, 0}, {4, 2, 4}, {0, 4, 3}}};
        matrix_T invP = {3, 3, {{1, 4, 0}, {4, 2, 4}, {0, 4, 3}}};
        matrix_T PinvP = {3, 3, {{1, 4, 0}, {4, 2, 4}, {0, 4, 3}}};
        matrix_T U = {3, 3, {{0.6948, -0.5895, 0.0271}, {0, 0.7478, 0.9024}, {0, 0, 1.3305}}};
        matrix_T result = {3, 3, {{0.6948, -0.5895, 0.0271}, {0, 0.7478, 0.9024}, {0, 0, 1.3305}}};

        matrix_T X = {2, 1, {{0}, {0}}};
        matrix_T X_dot = {2, 1, {{0}, {0}}};
        matrix_T Xtmp = {2, 1, {{0}, {0}}};
        matrix_T PX = {2, 2, {{30*30*2, 0}, {0, 10*10}}};
        matrix_T Ptmp = {2, 2, {{100, 0}, {0, 100}}};
        matrix_T R = {2, 2, {{30*30, 0},{0, 5*5}}};
        matrix_T Q = {2, 2, {{0.0005*0.0005*0.025, 0}, {0, 100*0.25*0.25*0.025}}};
        matrix_T F = {2, 2, {{0, 1}, {0, 0}}};
        matrix_T H = {2, 2, {{1, 0},{0, 1}}};
        matrix_T G = {2, 1, {{0, 1}}};
        matrix_T Inov = {2, 1, {0,0}};
        matrix_T IF = {2, 2, {{1, 0.025}, {0, 1}}};//F discret
        /*
        matrix_T c;
        matrix__init__(& c, 3, 3);

        printf("a = %f:\n",sqrt(3));
        matrix_print(& a);

        matrix_mul(& c, & a, & b);

        printf("\n");
        printf("P = :\n");
        matrix_print(& P);

        printf("\n");
        printf("c=a*b = :\n");
        matrix_print(& c);

        matrix_Low_Inv(& c, & a);
        printf("\n");
        printf("Inv(a) = :\n");
        matrix_print(& c);
        printf("\n");
        printf("Chol(P) = :\n");
        cholesky(& L,  & P);
        matrix_print(& L);

        matrix_Trans(& LT,& L);
        printf("Chol(P)T = :\n");
        matrix_print(& LT);
        matrix_mul(& LLT, & LT, & L);
        printf("L*LT = :\n");
        matrix_print(& LLT);
        matrix_Low_Inv(& invL, & LT);
        matrix_Trans(& invLT,& invL);
        matrix_mul(& invP, & invLT, & invL);
        matrix_mul(& PinvP, & P, & invP);

        printf("inv(P) = :\n");
        matrix_Inv_U(& invP,& L);
        matrix_print(& invP);

        printf("P*inv(P) = :\n");
        matrix_mul(& PinvP, & P, & invP);
        matrix_print(& PinvP);
        printf("inv(P) = :\n");
        matrix_Inv_U(&result,&U) ;
        matrix_print(& result);
        printf("\n\n");
        */
        ///////////////////////////////////////////////////////////////////////////////////
        //Boucle en temps
    ///////////////////////////////////////////////////////////////////////////////////

    fichier = fopen("res.txt", "w");
        Mesures = fopen("Mesures.txt", "r");

    if (fichier != NULL & Mesures != NULL)
    {

        fprintf(fichier, "X1       X2       P11       P12      P21      P22\n");
                fprintf(fichier, "%f %f %f %f %f %f\n", X.data[0][0],X.data[1][0],PX.data[0][0],PX.data[0][1],PX.data[1][0],PX.data[1][1]);
                //printf("P0 : %f %f %f %f \n", PX.data[0][0],PX.data[0][1],PX.data[1][0],PX.data[1][1]);
                for(int i=2;i<=4000;i++){
                        fscanf(Mesures, "%f %f %f", &gam,&xmes,&vmes);
                        //printf("gam = %f, vmes = %f\n",gam,xmes);

                        //////////////////////////////////////////////////////////////////////////////
                        //Prediction
                        /////////////////////////////////////////////////////////////////////////////

                        //printf("X1 %f X2 %f\n",X.data[0][0],X.data[1][0]);
                        X_dot.data[0][0] = X.data[1][0];
                        X_dot.data[1][0] = gam;
                        for(size_t k=0;k<X.row_n;k++){Xtmp.data[k][0]=X.data[k][0];}
                        matrix_add(&X,&Xtmp,&X_dot,1.0,0.025);
                        //printf("gam %f\n",gam);
                        //printf("X1 %f X2 %f\n",X.data[0][0],X.data[1][0]);
                        for(size_t k=0;k<PX.row_n;k++){
                                for(size_t j=0;j<PX.col_n;j++){
                                        Ptmp.data[k][j]=PX.data[k][j];
                                }
                        }
                        kalman_prediction(& PX, & Ptmp,& IF,& Q);
                        printf("P pred : %f %f %f %f \n", PX.data[0][0],PX.data[0][1],PX.data[1][0],PX.data[1][1]);
                        printf("X pred : %f %f  \n", X.data[0][0],X.data[0][1]);

                        /////////////////////////////////////////////////////////////////////////////////
                        //Update
                        /////////////////////////////////////////////////////////////////////////////////
                        Inov.data[0][0] = xmes - X.data[0][0];
                        Inov.data[1][0] = vmes - X.data[1][0];
                        printf("Inov : %f %f\n",Inov.data[0][0],Inov.data[1][0]);
                        if(i>2000 & i<3000 ){}
                                else{
                                        printf("!!!!!!!!!!!!!!!!");
                        kalman_update(&X,& PX,& H,& R,& Inov);
                        printf("P up : %f %f %f %f \n", PX.data[0][0],PX.data[0][1],PX.data[1][0],PX.data[1][1]);
                        printf("X up : %f %f  \n", X.data[0][0],X.data[0][1]);
                                }
                        fprintf(fichier, "%f %f %f %f %f %f\n", X.data[0][0],X.data[1][0],PX.data[0][0],PX.data[0][1],PX.data[1][0],PX.data[1][1]);
                }

        fclose(fichier);
                fclose(Mesures);
    }


}
