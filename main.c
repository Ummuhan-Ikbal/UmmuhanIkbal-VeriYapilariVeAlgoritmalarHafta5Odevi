#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tek bir hasta ve dugum (node) yapısı
struct Node {
    int id;
    char isim[50];
    char durum[20];
    struct Node* next;
};

// 1. KUYRUK (QUEUE) FONKSİYONLARI - Bekleyenler
void enqueue(struct Node** front, struct Node** rear, int id, char isim[]) {
    struct Node* yeni = (struct Node*)malloc(sizeof(struct Node));
    yeni->id = id;
    strcpy(yeni->isim, isim);
    strcpy(yeni->durum, "bekliyor");
    yeni->next = NULL;

    if (*rear == NULL) {
        *front = yeni;
        *rear = yeni;
    } else {
        (*rear)->next = yeni;
        *rear = yeni;
    }
}

struct Node dequeue(struct Node** front, struct Node** rear) {
    struct Node bos;
    bos.id = -1;

    if (*front == NULL) {
        printf("Kuyruk bos!\n");
        return bos;
    }

    struct Node* temp = *front;
    struct Node kopya = *temp; // Bilgiyi sakla

    *front = (*front)->next;
    if (*front == NULL) {
        *rear = NULL;
    }

    free(temp);
    return kopya;
}

// 2. YIĞIN (STACK) FONKSİYONLARI - Muayene Odası
void push(struct Node** top, struct Node hasta) {
    struct Node* yeni = (struct Node*)malloc(sizeof(struct Node));
    yeni->id = hasta.id;
    strcpy(yeni->isim, hasta.isim);
    strcpy(yeni->durum, "muayenede");
    yeni->next = *top;
    *top = yeni;
}

struct Node pop(struct Node** top) {
    struct Node bos;
    bos.id = -1;

    if (*top == NULL) {
        printf("Yigin bos!\n");
        return bos;
    }

    struct Node* temp = *top;
    struct Node kopya = *temp;

    *top = (*top)->next;
    free(temp);
    return kopya;
}

// 3. BAĞLI LİSTE FONKSİYONU - Geçmiş Kayıtlar
void ekleGecmis(struct Node** head, struct Node hasta) {
    struct Node* yeni = (struct Node*)malloc(sizeof(struct Node));
    yeni->id = hasta.id;
    strcpy(yeni->isim, hasta.isim);
    strcpy(yeni->durum, "tamamlandi");
    yeni->next = NULL;

    if (*head == NULL) {
        *head = yeni;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = yeni;
    }
}

// EKRANA YAZDIRMA FONKSİYONLARI
void yazdirKuyruk(struct Node* head) {
    printf("--- Bekleyen Hastalar ---\n");
    if (head == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    while (head != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", head->id, head->isim, head->durum);
        head = head->next;
    }
}

void yazdirYigin(struct Node* head) {
    printf("--- Muayene Odasindaki Hastalar ---\n");
    if (head == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    while (head != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", head->id, head->isim, head->durum);
        head = head->next;
    }
}

void yazdirGecmis(struct Node* head) {
    printf("--- Tamamlanan Hastalar ---\n");
    if (head == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    while (head != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", head->id, head->isim, head->durum);
        head = head->next;
    }
}

int main() {
    // İşaretçiler (Pointers) tanımında başlangıç
    struct Node* qFront = NULL;
    struct Node* qRear = NULL;
    struct Node* sTop = NULL;
    struct Node* gecmisHead = NULL;

    // 1. Hastaları kaydet
    enqueue(&qFront, &qRear, 1, "Ahmet");
    enqueue(&qFront, &qRear, 2, "Mehmet");
    enqueue(&qFront, &qRear, 3, "Ayse");

    // 2. Ahmet'i muayeneye al ve tamamla
    struct Node h1 = dequeue(&qFront, &qRear);
    if (h1.id != -1) {
        push(&sTop, h1);
        struct Node h1_bitti = pop(&sTop);
        ekleGecmis(&gecmisHead, h1_bitti);
    }

    // 3. Mehmet'i muayeneye al ve tamamla
    struct Node h2 = dequeue(&qFront, &qRear);
    if (h2.id != -1) {
        push(&sTop, h2);
        struct Node h2_bitti = pop(&sTop);
        ekleGecmis(&gecmisHead, h2_bitti);
    }

    // Beklenen Son Çıktı
    printf("=== Tum Islemler Sonrasi ===\n");
    yazdirKuyruk(qFront);
    yazdirYigin(sTop);
    yazdirGecmis(gecmisHead);

    return 0;
}