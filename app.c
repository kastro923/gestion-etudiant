#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_NOM 25
//Déclaration du type structuré Date
typedef struct {
    unsigned int jour;
    char mois[15];
    unsigned int annee;
}Date;

//Déclaration du type structuré Etudiant
typedef struct {
    char nom[25];
    char prenom[25];
    char parcourtTypes[25];
    char matricule[20];
    char lieu[25];
    unsigned int niveau;
    char sexe[10];
    Date dateDeNaissance;
}Etudiant;



void menu();

//Prototype du Sous-programme qui recherche si un étudiant de matricule M donné est présent
int rechercheEtudiant(char *matriculeEtu);

//Prototype du sous-programme d'affichage permettant d'afficher un étudiant
void afficheEtudiant(Etudiant etu);
void afficheGroupeEtudiant();

//Prototype du sous-programme permettant de créer un nouveau étudiant et de l'ajouter dans le groupe
void addNewStudent();

//Prototype du sous-programme permettant de faire interagi le programme avec un utilisateur.
void menu();

void decision(char *pointeurOpt);
void decision2(char *pointeurOpt);

void saveStudent(Etudiant etud);

int nombreEtudiant();

void addAbsence(char *date, char *matricule);
void saveAbsence();
int nbrAbsence(char *matricule);
int nbrtotalAbsence();
void listAbsence();


int main()
{
    printf("____________________BIENVENU____________________ \n");
    menu(); //L'appel de cette fonction lancera le menu
    printf("____________________________Au revoir_____________________________ \n\n");

    return 0;
}


//Implémentation du programme menu
void menu(){
    char option[3] = "NON";
    while((strcmp(option, "OUI") !=0) && (strcmp(option, "oui") !=0)){  //while pour repéter le menu tant que l'utilisateur n'entre pas OUI ou oui au moment indiquer
        int choixMenu;
        printf("\n\n  ==================  Menu ==================\n\n");
        printf("1 - Ajouter des etudiant dans le groupe.\n");
        printf("2 - Rechercher un etudiant.\n");
        printf("3 - Afficher tous les etudiants deja enregistrer.\n");
        printf("4 - Determiner le nombre d'etudiant enregistrer.\n");
        printf("5 - Ajouter des absents.\n");
        printf("6 - Determiner le nombre d'absence d'un etudiant donnee.\n");
        printf("7 - Liste des absents.\n");
        printf("8 - Quitter le programme.\n ");
        printf("Entrez votre choix ?  \t");
        scanf("%d", &choixMenu);
        printf("\n");

        switch(choixMenu)
        {
            case 1:
                addNewStudent();
                decision(option);
                break;
            case 2:
                printf("Entrez le matricule de l'etudiant que vous rechercher :");
                char matEtudiant[8];
                scanf("%s", matEtudiant);
                char* deci="NON";
                if(rechercheEtudiant(matEtudiant)==1)//pour afficher OUI ou NON comme resultat de la recherche
                    deci="OUI";
                printf("L'etudiant de matricule %s est-il present : %s\n", matEtudiant, deci);
                decision(option);
                break;
            case 3:
                afficheGroupeEtudiant();
                decision(option);
                break;
            case 4:
                printf("Le nombre d'etudiant est %d etudiant(s)\n", nombreEtudiant());
                decision(option);
                break;
            case 5:
                saveAbsence();
                printf("Save reussi");
                decision(option);
                break;
            case 6:
                printf("Entrez le matricule de l'etudiant:\t");
                char matEtud[8];
                scanf("%s", matEtud);
                int i = nbrAbsence(matEtud);
                printf("%s a : %d absence(s).\n", matEtud, i);
                decision(option);
                break;
            case 7:
                listAbsence();
                decision(option);
                break;
            case 8:
                decision2(option);
                break;
            default:
                decision(option);
                break;

        }
    }

    printf("\nMerci d'avoir utiliser notre mini-programme. :)\n");
    printf("\n  =========================  Arret =========================\n\n");
}


//Implémentation du sous-programme rechercheEtudiant
int rechercheEtudiant(char matriculeEtu[20]){//Fonction
    int nbrEtudiant=nombreEtudiant();
    FILE *fichier = NULL;
    int i = 0;//int i = -1;
    int verification = 0;
    fichier = fopen("Data/SaveEtudiant.sav", "r");
    if(fichier != NULL){
        Etudiant etud;
        while(!(feof(fichier))&&nbrEtudiant>0){
            fscanf(fichier,"%s %s %d %s %d %s %s %s %d %s", etud.nom, etud.prenom, &etud.dateDeNaissance.jour, etud.dateDeNaissance.mois, &etud.dateDeNaissance.annee, etud.lieu, etud.matricule, etud.parcourtTypes, &etud.niveau, etud.sexe);
            if(strcmp(etud.matricule, matriculeEtu)!=0)
                /*  Ici la condiction pour sortir de la boucle while est que:
                    Soit on trouve le matricule
                    soit on parcourt tout le groupe d'étudiant
                */
                i++;
            nbrEtudiant--;
            }
        fclose(fichier);
        nbrEtudiant=nombreEtudiant();
        if(i < nbrEtudiant)//si est égale à la taille du groupe d'étudiant
            verification = 1;
    }
    return verification;
}

//Implémentation du sous-programme afficheEudiant
void afficheEtudiant(Etudiant etu){
    printf("\n---------------------------------------------------------------------------------------------\n");
    printf("Nom : %s\t Prenom : %s\t Date et lieu de naissance : %d %s %d a %s\n",
            etu.nom, etu.prenom, etu.dateDeNaissance.jour, etu.dateDeNaissance.mois,
             etu.dateDeNaissance.annee, etu.lieu);
    printf("Matricule : %s\t Parcourt-Types : %s\t Niveau : %d\t Sexe : %s \n", etu.matricule,
            etu.parcourtTypes, etu.niveau, etu.sexe);
}

void afficheGroupeEtudiant(){
    int nbrEtudiant=nombreEtudiant();
    FILE *fichier = NULL;
    fichier = fopen("SaveEtudiant.sav", "r");
    if(fichier != NULL){
        printf("Voici les %d membres du groupe d'etudiant\n", nbrEtudiant);
        Etudiant etud;
        while(!(feof(fichier))&&nbrEtudiant>0){
            fscanf(fichier,"%s %s %d %s %d %s %s %s %d %s", etud.nom, etud.prenom, &etud.dateDeNaissance.jour, etud.dateDeNaissance.mois, &etud.dateDeNaissance.annee, etud.lieu, etud.matricule, etud.parcourtTypes, &etud.niveau, etud.sexe);
            afficheEtudiant(etud);
            nbrEtudiant--;
        }
        fclose(fichier);
    }
}

//Implémentation du sous-programme addNewStudent celle-ci permet de créer un nouveau etudiant
//Et de l'ajouter dans le groupe
void addNewStudent(){
    printf("Combien d'etudiant voulez vous ajouter au groupe?  ");
    int nEtudiant;
    scanf("%d", &nEtudiant);
    for (int i = 0; i < nEtudiant; i++)
    {
        printf("\nEntrez les informations de l'etudiant %d\n", i+1);
        Etudiant newStudent;
        printf("Entrez son nom : ");
        scanf("%s", newStudent.nom);
        printf("Entrez son prenom : ");
        scanf("%s", newStudent.prenom);
        printf("Entrez son jour de naissance : ");
        scanf("%d", &newStudent.dateDeNaissance.jour);
        printf("Entrez son mois de naissance : ");
        scanf("%s", newStudent.dateDeNaissance.mois);
        printf("Entrez son annee de naissance : ");
        scanf("%d", &newStudent.dateDeNaissance.annee);
         printf("Entrez son lieu de naissance : ");
        scanf("%s", newStudent.lieu);
        printf("Entrez son sexe (M ou F) : ");
        scanf("%s", newStudent.sexe);
        printf("Entrez son matricule : ");
        scanf("%s", newStudent.matricule);
        printf("Entrez son parcourt-types : ");
        scanf("%s", newStudent.parcourtTypes);
        printf("Entrez son niveau : ");
        scanf("%d", &newStudent.niveau);
        saveStudent(newStudent); //Nous enregistrons ainsi les données du nouveau étudiant dans notre fichier.
    }
}


void saveStudent(Etudiant etud){
    FILE *fichier = NULL;
    fichier = fopen("SaveEtudiant.sav", "a+");
    if(fichier != NULL)
        fprintf(fichier,"%s %s %d %s %d %s %s %s %d %s\n",etud.nom, etud.prenom, etud.dateDeNaissance.jour, etud.dateDeNaissance.mois, etud.dateDeNaissance.annee, etud.lieu, etud.matricule, etud.parcourtTypes, etud.niveau, etud.sexe);
    fclose(fichier);

}


int nombreEtudiant(){
    int a=-1;
    FILE *fichier = NULL;
    fichier = fopen("SaveEtudiant.sav", "r+");
    if(fichier != NULL){
        Etudiant etud;
       while(!(feof(fichier))){
            fscanf(fichier,"%s %s %d %s %d %s %s %s %d %s", etud.nom, etud.prenom, &etud.dateDeNaissance.jour, etud.dateDeNaissance.mois, &etud.dateDeNaissance.annee, etud.lieu, etud.matricule, etud.parcourtTypes, &etud.niveau, etud.sexe);
            a++;
        }
        fclose(fichier);
    }
    return a;
}

void decision(char *pointeurOpt){
    printf("\nVoulez vous quitter ( 'OUI' ou 'NON' ) ?  \t");
    scanf("%s", pointeurOpt);
}
void decision2(char *pointeurOpt){
    printf("\nVoulez vous vraiment quitter le mini-programme ( 'OUI' ou 'NON' ) ?  \t");
    scanf("%s", pointeurOpt);
}


void addAbsence(char abs[20], char matricule[20]){
    FILE *fichier = NULL;
    fichier = fopen("SaveAbsence.sav", "a");
    if(fichier != NULL){
        fprintf(fichier,"%s %s\n", matricule, abs);
        fclose(fichier);
    }
    
}

void saveAbsence(){
    int n;
    printf("Entrer le nombre absence que vous souhaitez enregistrer : ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        char m[20];
        printf("Entrer le matricule de l'etudiant absent : ");
        scanf("%s", m);
        //if(rechercheEtudiant(m)==1){
            printf("Entrer la date d'absence (jj/mm/aaaa) : ");
            char d[20];
            scanf("%s", d);

            addAbsence(d, m);
       // }
       // else
          //  printf("Ce matricule ne correspond à aucun etudiant");
    }
}

int nbrAbsence(char matricule[8]){
    int a=0;
    
    FILE *fichier = NULL;
    fichier = fopen("SaveAbsence.sav", "r");
    if(fichier != NULL){
        while(!(feof(fichier))){
            char m[20];
            char d[20];
            fscanf(fichier,"%s %s\n", m, d);
            if(strcmp(m,matricule)==0)
                a++;
        }
        fclose(fichier);
    }
    return a;
}

int nbrTotalAbsence(){
    int a=0;
    FILE *fichier = NULL;
    fichier = fopen("SaveAbsence.sav", "r");
    if(fichier != NULL){
        while(!(feof(fichier))){
            char m[20];
            char d[20];
            fscanf(fichier,"%s %s\n", m, d);
                a++;
        }
        fclose(fichier);
    }
    return a;
}

void listAbsence(){
    int nbr=nbrTotalAbsence();
    FILE *fichier = NULL;
    fichier = fopen("SaveAbsence.sav", "r");
    if(fichier != NULL){
        printf("Voici la des %d absences \n", nbr);
        int i = 1;
        while(!(feof(fichier)) && nbr>0){
            char m[20];
            char d[20];
            fscanf(fichier,"%s %s", m, d);
            printf("%d-\t %s\t %s\n", i, m, d);
            i++;
            nbr--;
        }
        fclose(fichier);
    }
}
