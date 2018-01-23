# include <memory>
# include <iostream>

int main()
{
  {
    double x = 3.14, y = 1.54, z = 2.28;
    int    i = 3;
    double array[3] = { 1., 2., 3. };
    double *pt_x = &x;
    double *pt_y = &y, *pt_z = &z;
    double* *pt_pt_x = &pt_x;//Pointeur sur le pointeur de x
    double *pt_arr = array; // Pointeur sur le 1er élément de array
    ++pt_arr; // Pointe sur l'élément suivant ( le second )
    --pt_arr; // Pointe sur l'élément précédent ( le premier )
    pt_arr += 2; // Pointe deux éléménts plus loin ( le 3e )
    *pt_arr = 4; // On affecte la valeur 4 à l'élément pointé par pt_arr
    pt_arr[2] = 1;// on affecte 1 à la valeur située 2 éléments plus loin
    pt_arr -= 2; x = pt_arr[1]; // x devient égal à 2 ( équiv x = *(pt_arr+1) )
    pt_x = nullptr; // pt_x pointe maintenant sur 'rien' => pointeur nul
    std::cout << "array : " << *(pt_arr++) << " " << *(pt_arr++) 
              << ' ' << *(pt_arr++) << std::endl;
    pt_arr += 3;// pt_arr pointe trois valeurs aprés celle pointée
    double* pt_arr2 = pt_arr - 2;// pt_arr2 pointe deux valeurs avant pt_arr
    *(pt_arr2+1) = 3;// Equiv. à pt_arr2[1] 
  }
  { 
    // On réserve de la mémoire pour un double et on pointe dessus :
    std::unique_ptr<double> un_pt; // Pointe par défaut sur nullptr
    std::unique_ptr<double> un_pt_v = std::make_unique<double>(4.56);
    std::unique_ptr<double> un_pt_w = std::move(un_pt_v); // un_pt_w pointe sur 4.56, mais
                                                          // un_pt_v ne pointe plus sur rien.
    double a = un_pt_w[0];
    std::cout << *un_pt_w; // Même interface que pointeur standard mais pas d'inc/décrémentation
    // A la fin du bloc, le dernier pointeur à pointer sur la valeur la détruit en mémoire.
  }
  {
    // On réserve de la mémoire pour un double et on pointe dessus :
    std::shared_ptr<double> un_pt;// Pointe par défaut sur nullptr
    std::shared_ptr<double> un_pt_v = std::make_shared<double>(4.56);
    std::shared_ptr<double> un_pt_w = un_pt_v; // un_pt_w pointe sur 4.56
                                               // un_pt_v pointe sur 4.56
    int ref_count = un_pt_w.use_count();// Nombre de pointeurs pointant sur 4.56 ( ici 2 )
    un_pt_v = std::make_shared<double>(3.14);// un_pt_v pointe sur 3.14
    ref_count = un_pt_w.use_count();// Cette fois ci, on retourne 1
    un_pt_w = nullptr; // un_pt_w pointe sur nul, la valeur 4.56 est détruite car aucun pointeur dessus
    // La valeur 3.14 est détruite lorsque un_pt_v est détruit à la fin du bloc ( aucun pointeur dessus )
  }
    
}