#include "Sunday.h"

int main() {

    string Text;
    string Pattern;
    cout << "Chose scenario:\n";
    cout << "0. Insert your own text and pattern\n";
    cout << "1. Text = ABCABDABCABDABCDABCDA Pattern = ABCD\n";
    cout << "2. Text = aaaaaaabaaaaaa        Pattern = aaaaab\n";
    cout << "3. Text = aaaaaaabaaaaaa        Pattern = aaaab\n";
    cout << "4. Text = abcabcabcabcabc       Pattern = abcde\n";
    cout << "5. Text = abacabadabacaba       Pattern = abacaba\n";
    cout << "6. Text = marekpachnielmarekpachnielmarekpachnielmamamamamamamamarekpachnielelelel Pattern = pachniel\n";
    cout << "7. Text = baab  Pattern = aa\n";
    cout << "8. dlugi text z patternem modxq\n";
    // baab // aa
    int a; cin >> a;
    switch (a)
    {
    case 0:     cout << "\nText: "; cin >> Text; cout << "\nPattern :"; cin >> Pattern; break;
    case 1:     Text = "abcabdabcabdabcdabcda";  Pattern = "abcd";      break;
    case 2:     Text = "aaaaaaabaaaaaa";         Pattern = "aaaaab";    break;
    case 3:     Text = "aaaaaaabaaaaaa";         Pattern = "aaaab";     break;
    case 4:     Text = "abcabcabcabcabc";        Pattern = "abcde";     break;
    case 5:     Text = "abacabadabacaba";        Pattern = "abacaba";   break;
    case 6:     Text = "marekpachnielmarekpachnielmarekpachnielmamamamamamamamarekpachnielelelel";        Pattern = "pachniel";   break;
    case 7: Text = "baab"; Pattern = "aa"; break;
    case 8: Text = "MODXQMODXQMODXQMODXQMODXQMODXQMODXQRJATYDIMOFUGCLQURCLQECDRHVQSUWBVNTMRYKTDLWIXOQLDSWTMHMJXQEDMODXQQKPRNGPROXVFPEUAGBSXEXJEGPQBGIMODXQTOBXMNSHEQIPOIEFCGXLVUMODXYWUECXWMLPLLFRFYGCAAQYQFHQHMHMDIUJJIVMODXQNWVGFNSAQMFKJYMXIUQCAQLYUVVXMODXQYSJGJDYSNANCRDSXIHVKRNOJQKBAYTGXDYITJOCUKSSXMODXAISFVXGOXJHWWNRNEPHIQPNGLCJWFDVMLAI";
      Pattern = "MODXQ"; break;
    default:    Text = "ABCABDABCABDABCDABCDA";  Pattern = "ABCD";   cout << "wrong input, using default\n";   break;
    }
    cout << "\nScenario nr: " << a << '\n' << '\n';

    vector<int> resultsTab;
    
    // Zlozonosci:            [ Sunday Odczyt: Theta((t+1)/(w)) ]
    // Sunday       Worst: O(tp)    Best: Theta((t+1)/(w+1))        Memory: O(p)
    // SundayPary   Worst: O(tp)    Best: Theta((t+1)/(w+1))        Memory: O(p)
    // KMP          Worst: O(t+p)   Best  O(t)                      Memory: O(p)
    // Naiwny       Worst: O(tp)    Best: O(t)                      Memory: O(1)
    // BoyerMoore ???
    // RabinKarp ???

    resultsTab = sunday(Text, Pattern);
    cout << "Sunday: \n";
    for (unsigned int i = 0; i < resultsTab.size(); i++) {
        cout << "Match found at index " << resultsTab[i] << '\n';
    }
    cout << complexity << '\n' << '\n';

    resultsTab = kmp(Text, Pattern);
    cout << "Knuth Morris-Pratt: \n";
    for (unsigned int i = 0; i < resultsTab.size(); i++) {
        cout << "Match found at index " << resultsTab[i] << '\n';
    }
    cout << complexity << '\n' << '\n';

    resultsTab = sundayPairs(Text, Pattern);
    cout << "Sunday using pairs: \n";
    for (unsigned int i = 0; i < resultsTab.size(); i++) {
        cout << "Match found at index " << resultsTab[i] << '\n';
    }
    cout << complexity << '\n' << '\n';

    resultsTab = boyerMoore2(Text, Pattern);
    cout << "Boyer - Moore: \n";
    for (unsigned int i = 0; i < resultsTab.size(); i++) {
        cout << "Match found at index " << resultsTab[i] << '\n';
    }
    cout << complexity << '\n' << '\n';

    resultsTab = rabinKarp(Text, Pattern);
    cout << "Karp - Rabin: \n";
    for (unsigned int i = 0; i < resultsTab.size(); i++) {
        cout << "Match found at index " << resultsTab[i] << '\n';
    }
    cout << "no complexity for karpRabin" << '\n' << '\n';

    resultsTab = naive(Text, Pattern);
    cout << "Naive: \n";
    for (unsigned int i = 0; i < resultsTab.size(); i++) {
        cout << "Match found at index " << resultsTab[i] << '\n';
    }
    cout << complexity << '\n' << '\n';




    return 0;
}