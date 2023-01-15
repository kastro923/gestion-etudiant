#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Déclaration de l'enregistrement Date
 struct DATE {
    int jour;
    char mois[15];
    int annee;
};
typedef struct DATE Date;

//Déclaration de l'enregistrement Etudiant
struct ETUDIENT {
    char nom[25];
    char prenom[25];
    char matricule[20];
    char lieu[25];
    char sexe[10];
    Date dateDeNaissance;
};
typedef struct ETUDIENT Etudiant;


int rechercheEtudiant(char *matriculeEtu);

void afficheEtudiant(Etudiant etu);
void afficheGroupeEtudiant();


void addNewStudent();

void menu();

void decision(char *pointeurOpt);
void decision2(char *pointeurOpt);

void saveStudent(Etudiant etud);

int nombreEtudiant();



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
        printf("5 - Quitter le programme.\n ");
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


int rechercheEtudiant(char matriculeEtu[20]){//Fonction
    int nbrEtudiant=nombreEtudiant();
    FILE *fichier = NULL;
    int i = 0;//int i = -1;
    int verification = 0;
    fichier = fopen("SaveEtudiant.sav", "r");
    if(fichier != NULL){
        Etudiant etud;
        while(!(feof(fichier))&&nbrEtudiant>0){
            fscanf(fichier,"%s %s %d %s %d %s %s %s", etud.nom, etud.prenom, &etud.dateDeNaissance.jour, etud.dateDeNaissance.mois, &etud.dateDeNaissance.annee, etud.lieu, etud.matricule, etud.sexe);
            if(strcmp(etud.matricule, matriculeEtu)==0){
            	verification = 1;
            	break;
			}
            	
                            
            nbrEtudiant--;
            }
        fclose(fichier);
    }
    return verification;
}
//procedure afficheEudiant
void afficheEtudiant(Etudiant etu){
    printf("\n---------------------------------------------------------------------------------------------\n");
    printf("Nom : %s\t Prenom : %s\t Date et lieu de naissance : %d %s %d a %s\n",
            etu.nom, etu.prenom, etu.dateDeNaissance.jour, etu.dateDeNaissance.mois,
             etu.dateDeNaissance.annee, etu.lieu);
    printf("Matricule : %s\t Sexe : %s \n", etu.matricule, etu.sexe);
}

void afficheGroupeEtudiant(){
    int nbrEtudiant=nombreEtudiant();
    FILE *fichier = NULL;
    fichier = fopen("SaveEtudiant.sav", "r");
    if(fichier != NULL){
        printf("Voici les %d membres du groupe d'etudiant\n", nbrEtudiant);
        Etudiant etud;
        while(!(feof(fichier))&&nbrEtudiant>0){
            fscanf(fichier,"%s %s %d %s %d %s %s %s", etud.nom, etud.prenom, &etud.dateDeNaissance.jour, etud.dateDeNaissance.mois, &etud.dateDeNaissance.annee, etud.lieu, etud.matricule, etud.sexe);
            afficheEtudiant(etud);
            nbrEtudiant--;
        }
        fclose(fichier);
    }
}

//procedure addNewStudent celle-ci permet de créer un nouveau etudiant
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
        saveStudent(newStudent); //Nous enregistrons ainsi les données du nouveau étudiant dans notre fichier.
    }
}


void saveStudent(Etudiant etud){
    FILE *fichier = NULL;
    fichier = fopen("SaveEtudiant.sav", "a+");
    if(fichier != NULL)
        fprintf(fichier,"%s %s %d %s %d %s %s %s\n",etud.nom, etud.prenom, etud.dateDeNaissance.jour, etud.dateDeNaissance.mois, etud.dateDeNaissance.annee, etud.lieu, etud.matricule, etud.sexe);
    fclose(fichier);

}


int nombreEtudiant(){
    int a=-1;
    FILE *fichier = NULL;
    fichier = fopen("SaveEtudiant.sav", "r+");
    if(fichier != NULL){
        Etudiant etud;
       while(!(feof(fichier))){
            fscanf(fichier,"%s %s %d %s %d %s %s %s", etud.nom, etud.prenom, &etud.dateDeNaissance.jour, etud.dateDeNaissance.mois, &etud.dateDeNaissance.annee, etud.lieu, etud.matricule, etud.sexe);
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
