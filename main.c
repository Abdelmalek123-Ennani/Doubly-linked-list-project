// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*----------------------------- declaration of different sructs -------------------------------- */
typedef struct repo_t repo_t;
typedef struct liste_t liste_t;
typedef struct node_t node_t;
typedef struct contact_t contact_t;

struct  repo_t {
   liste_t *lists;
   int nbre;
};

struct liste_t {
    int nbr;
    node_t *T;
};

struct node_t {
    node_t *next;
    node_t *prev;
    contact_t *contact;
};

struct contact_t {
    char nom[40];
    char prenom[40];
    char email[40];
    char phone[10];
};

// initialisation
repo_t *initialisation() {
    // memory allocation for repo 
    repo_t *repository = malloc(sizeof(*repository));
    // set the nbre to 26 (number of lists)
    repository->nbre = 26;
    // memory allocation for our lists (we want 26 lists) 
    repository->lists = malloc(sizeof(*repository->lists) *  repository->nbre);
    
    // loop over lists and set T to null (cause there are no nodes yet) and nbr to 0
    int i;
    for (i=0; i< repository->nbre ;i++) {
        repository->lists[i].T = NULL;
        repository->lists[i].nbr = 0;
    }
   

   // return the repo
   return repository;
   
}


// add a contact (a node )
void ajouterUnContact(liste_t *list , contact_t *person) {
    
    // get  the first letter of the name to know the index of list that we want to add the node to 
    char firstLetter = toupper(person->nom[0]); // first letter of the name
    int listIndice = firstLetter - 65;          // get the index
    node_t *node =  list[listIndice].T;        // select the list (based on the index)
    
    
    // check if guven person is already exists
    while(node != NULL) {
        char *name = node->contact->nom;
        char *prenom = node->contact->prenom;
        if ( strcmp(name , person->nom) == 0 && strcmp(prenom , person->prenom) == 0 ) {
            printf("\n------------------------------------\n");
            printf("The person is already exists \n");
            printf("---------------------------------------\n");
            return;
        }
      
        node = node->next;
    }
    
    // if list is empty we add the node as the first one
    if ( list[listIndice].T == NULL ) {
        node_t *node = malloc(sizeof(*node));
        node->next = NULL;
        node->prev = NULL;
        node->contact = person;
        list[listIndice].T = node;
        list[listIndice].nbr += 1;
    } else {  // if there is already an element / elements

         // memory allocation for our node
        node_t *node = malloc(sizeof(*node));
        node->next = list[listIndice].T;
        node->prev = NULL;
        node->contact = person;
        node->next->prev = node;
        list[listIndice].T = node;
        list[listIndice].nbr += 1;
    }
}

// printOut our lists and their contacts information
void afficher(liste_t *list , int nbre) {
    char c;
    int i;
    // loop over lists
    for ( i=0; i<nbre ; i++ ) {
        // check if the list has at least one element
       if ( list[i].nbr > 0 ) {
           // get the letter based on the index (ex : 65 + 0 = A // 65 + 2 = B ....)
            int charAscci = 65 + i;
            c = charAscci;
            printf("contacts that's begin with letter : %c \n" , c);
            node_t *nodeT = list[i].T;
            int counter = 0;
             while(nodeT !=NULL) {
                printf("Contact N°: %d : \n" , ++counter);
                printf("\t firstName => %s \n" , nodeT->contact->nom);
                printf("\t lastName => %s \n" , nodeT->contact->prenom);
                printf("\t email => %s \n" , nodeT->contact->email);
                printf("\t phone => %s \n" , nodeT->contact->phone);
                nodeT = nodeT->next;
            }
            printf("---------------------- \n");
       }
    }
}


// print out a list of contacts that's begin with a specific number
void afficherParLetter(liste_t *list , int nbre , char c) {
     
     // get the index based on the letter
     int indice = (int)toupper(c) - 65;
     
     // check if there is no contacts (list is empty)
     if ( list[indice].nbr == 0 ) {
         printf("---------------------------- \n");
         printf("There is no contact that's begin with the letter %c \n" , c);
         printf("----------------------------- \n");
         return;
     }
     
     // if there is contacts (not empty)
     node_t *nodeT = list[indice].T;
     int counter = 0;
     printf("\n-----------------------------------------\n");
     printf("contact that begin with the letter %c \n" , c);
     while(nodeT !=NULL) {
        printf("Contact N°: %d : \n" , ++counter);
        printf("\t firsName => %s \n" , nodeT->contact->nom);
        printf("\t lastName => %s \n" , nodeT->contact->prenom);
        printf("\t email => %s \n" , nodeT->contact->email);
        printf("\t phone => %s \n" , nodeT->contact->phone);
        nodeT = nodeT->next;
     }
     printf("-----------------------------------------\n");
     
}

// update data of a given person
void updatePersonData(liste_t *list , char *email , char *nom) {
    
    // get the index of the target list (where the person exists)
    int indice = toupper(nom[0]) - 65;
    node_t *node = list[indice].T;
    
    // loop over target list
    while( node ) {
        
        // if the perosn exists then update it's informations
        if ( strcmp(node->contact->nom , nom) == 0 && strcmp(node->contact->email , email) == 0 ) {
            // get a copy of peron's information
            char *newName = node->contact->nom;
            char *newLastName =  node->contact->prenom;
            char *newEmail =  node->contact->email;
            char *newPhone =  node->contact->phone;
            
            int i = 0;
            int nbrChosen = -1;
            // ask the user to enter a number to update a spercif info
             printf("MENU :  \n");
             printf("\tyou want to change name ? : press 1 \n");
             printf("\tyou want to change lastName ? : press 2 \n");
             printf("\tyou want to change email ? : press 3 \n");
             printf("\tyou want to change phone ? : press 4 \n");
             printf("\tsave changes : press 5");
            while( nbrChosen != 5) {
            // get the chosen number by perosn
            printf("\nchoose a number from the menu : ");
            scanf("%d" , &nbrChosen);
            
            // update the specific info based on the user's choice
            switch(nbrChosen) {
                case 1 :
                     printf("Entrer le nouveau nom : ");
                     scanf("%s" , newName);
                     break;
                case 2 :
                     printf("Entrer le nouveau prenom : ");
                     scanf("%s" ,  newLastName);
                     break;
                case 3 :
                     printf("Entrer le nouveau email : ");
                     scanf("%s" ,  newEmail);
                     break;
                case 4 :
                     printf("Entrer le nouveau email : ");
                     scanf("%s" ,  newPhone);
                     break;
                default:  // if the user pressed a number that's is not 1,2,3,4 then apply the changes
                     strcpy(node->contact->nom , newName);
                     strcpy(node->contact->prenom ,newLastName);
                     strcpy(node->contact->email , newEmail);
                     strcpy(node->contact->phone , newPhone);
                     nbrChosen = 12;
                   return;
            }
            }
            
           return;
        }
        
        node = node->next;
    }
    
}


// search for a person by name (will print more than one if there is multiple perons with the same name)
void searchForAperson(liste_t *list , char *name) {
    
    int indice = toupper(name[0]) - 65;
    node_t *node = list[indice].T;
    
    printf("--------------------------------------------\n");
    printf("Les personnes qui ont le nom %s : \n" , name);
    int i = 0;
    while(node != NULL) {
        if ( strcmp(node->contact->nom , name) == 0 ) {
            ++i;
            printf("Personne N° : %d \n" , i);
            printf("\tnom => %s \n" , node->contact->nom);
            printf("\tprenom => %s \n" , node->contact->prenom);
            printf("\temail => %s \n" , node->contact->email);
            printf("\tphone => %s \n" , node->contact->phone);
        }
        node = node->next;
    }
    
    if ( i == 0 ) {
        printf("OOps il n ya aucun personne avec le nom : %s dans la liste \n");
        printf("--------------------------------------------\n");
    } else {
        printf("--------------------------------------------\n");
    }
}


// delete a person using it's name and email
void deleteApersonFromList(liste_t *liste, char *name , char *email) {
    int indice = toupper(name[0]) - 65;
     node_t *node = liste[indice].T;
     node_t *prev = NULL;
    
    while(node != NULL) {
         if ( strcmp(name , node->contact->nom) == 0 && strcmp(email , node->contact->email) == 0 ) {
          
             // if it is the last element
             if ( node->next == NULL ) {
                prev->next = NULL;
                free(node);
                return;
             } else if( node->prev == NULL ){ // the it is the first 
                 liste[indice].T = node->next;
                 node->next->prev = NULL;
                 free(node);
                 return;
             } else { // if it is on the middle middle
                 
                prev->next = node->next;
                node->next->prev = prev;
                free(node);
                return;
                 
             }
          
         }
        prev = node;
        node = node->next;
    }
}

/*
  This is not the final version of the project
  I'm aiming to add more functionalities to the project in upcoming days
*/

int main() {
   
    repo_t *repository = initialisation();
    // add a person
    contact_t *person = malloc(sizeof(*person));
    strcpy(person->nom , "Abdelmalek");
    strcpy(person->prenom , "Ennani");
    strcpy(person->phone , "06213873");
    strcpy(person->email , "test@gmail.com");
    ajouterUnContact(repository->lists , person);
    // add a new peroson
    contact_t *Sperson = malloc(sizeof(*Sperson));
    strcpy(Sperson->nom , "Sameh");
    strcpy(Sperson->prenom , "alaa");
    strcpy(Sperson->email , "Sameh@gmail.com");
    strcpy(Sperson->phone , "07123124232");
    ajouterUnContact(repository->lists , Sperson);
    
    // add an other person
    contact_t *Eperson = malloc(sizeof(*Eperson));
    strcpy(Eperson->nom , "Ahmed");
    strcpy(Eperson->prenom , "HG");
    strcpy(Eperson->phone , "06213873");
    strcpy(Eperson->email , "abdel@gmail.com");
    ajouterUnContact(repository->lists , Eperson);
    
    // add a new peron
    contact_t *Dperson = malloc(sizeof(*Dperson));
    strcpy(Dperson->nom , "Amire");
    strcpy(Dperson->prenom , "Kali");
    strcpy(Dperson->phone , "0621356792");
    strcpy(Dperson->email , "amire@gmail.com");
    ajouterUnContact(repository->lists , Dperson);


    // aficher la liste
    afficher(repository->lists , repository->nbre);
    // aficher par lettre
    afficherParLetter(repository->lists , repository->nbre , 'T');
    
    // updqte a person's info
    // updatePersonData(repository->lists , "test@gmail.com" , "Abdelmalek Ennani");
    
    // print out lists
    // afficher(repository->lists , repository->nbre);

     // serach for a person (using it's name)
     searchForAperson(repository->lists , "Ahmed");
     
     // delete a person
     deleteApersonFromList(repository->lists , "Ahmed" , "abdel@gmail.com");
     
     // print out lists
     afficher(repository->lists , repository->nbre);

    return 0;
}
