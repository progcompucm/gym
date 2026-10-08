Nos piden:
    El indice de la puerta con el anagrama "regalo".

Ejemplo:
n = 10
r[i] = { 1, 9, 8, 14, 3, 3, 21, 3, 12 }
p[i] = { HVSfJM URadpn OQIZWt svkMpe FcwIzU jUHodr OjLXUr mDgbPz jUODrl XsUqGd }

Puerta 0: GUReIL
Puerta 1: LIruge
Puerta 2: GIAROl
Puerta 3: orgIla
Puerta 4: RoiUlG
Puerta 5: gRElao
Puerta 6: LgIURo
Puerta 7: rIlgUe
Puerta 8: gRLAoi
Puerta 9: LgIeU

La puerta 5 contiene el anagrama.

Estrategia candidata:
Tenemos el abcdario:
    vector<char> alph;
    map<ll, ll> char_idx;
    for(char l = 'a', ll i = 0; l <= 'z'; l++, i++){
        alph.pb(l);
        char_idx[i] = l;
    }
Las rotaciones:
    vll r(n);
    each(&x : r) cin >> x;
Las palabras de cada puerta:
    vector<string> p(n);
    each(&x : p) cin >> p;
Iteramos sobre p:
    rep(i, 0, 6){

    }
En cada iteración sabemos que la rotación aplicada es r[i].
Para cada caracter, aplicamos la rotación.
    string s;
    each(c : p[i]){
        s += alph[(char_idx[c] + r[i]) % 25]
    }
Luego de aplicar la rotación, sabemos que nuestro target es:
    target = "regalo"
Pero como es un anagrama, mejor comparar con el str ordenado:
    sort(all(target)) == sort(all(s))
Si es true, entonces:
    p(i, endl).