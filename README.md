# linked-lists

# TEMA1 SDA

## Descrierea Funcționalităților

1. **Funcțiile de Inițializare**: Funcțiile de inițializare returnează un pointer.

2. **Adăugare și Eliminare în Coada**:
   - Am creat o funcție care adaugă un șir de caractere într-o coadă dacă acesta aparține unei anumite mulțimi.
   - Am implementat o funcție care elimină un element din coadă.

3. **Schimbare Sens**: Funcția `schimbaSensul` schimbă sensul cozii.

4. **Căutare Dreapta**: Funcția `search` caută un șir de caractere în dreapta mecanicului. Atunci când șirul este găsit, poziția mecanicului se schimbă și acesta se mută în vagonul care corespunde primului element din șirul căutat.

5. **Căutare Stânga**: Funcția `searchLeft` caută în stânga mecanicului un șir de caractere până la întâlnirea santinelei (`train->sentinel->prev`).

6. **Căutare Dreapta**: Funcția `searchRight` caută în dreapta mecanicului un șir de caractere până la întâlnirea santinelei (`train->sentinel->next`).

7. **Mutare**: Funcția `move`:
   - Dacă este apelată pentru mutarea la dreapta și mecanicul se află în ultimul vagon, se creează un nou vagon, se pune caracterul `#` în el și mecanicul se mută în acest nou vagon.
   - În celelalte situații, funcția doar mută mecanicul la stânga sau la dreapta.

8. **Executare**: Funcția `execute` scoate ultimul nod din coadă și execută comanda aferentă. La final, eliberăm memoria alocată pentru coadă și pentru tren.

9. **Împărțire Șir**: Funcția `splitString` împarte un șir de caractere în două subșiruri: înainte și după caracterul `' '`.

10. **Inserare Stânga/Dreapta**:
    - Funcțiile `insertLeft` și `insertRight` creează un nod nou în stânga sau în dreapta, inserează caracterul `#` în acest nou nod și mută mecanicul aici.
