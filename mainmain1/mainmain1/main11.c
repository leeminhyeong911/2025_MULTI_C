#include <stdio.h>              // 표준 입출력 함수 사용을 위한 헤더 (printf 등)
#include <stdlib.h>             // 일반 유틸(난수 rand, srand 등) 함수 헤더
#include <time.h>               // 시간 관련 함수(time) 헤더: 난수 시드 설정에 사용

#define Key_a 97                // 문자 'a'의 ASCII 코드 값
#define Key_z 122               // 문자 'z'의 ASCII 코드 값

int swap(char* a, char* b)      // 두 문자의 값을 맞바꾸는 함수 (반환형이 int로 되어 있지만 실제로 값은 반환하지 않음)
{
    char c;                     // 임시 보관용 변수
    c = *a;                     // c에 a가 가리키는 문자 저장
    *a = *b;                    // a 자리에 b가 가리키는 문자 대입
    *b = c;                     // b 자리에 c(원래 a의 값) 대입 -> 교환 완료
}

int main()                      // 프로그램 시작점
{
    char random[Key_z - Key_a + 1]; // 'a'~'z' 총 26개 문자를 담을 배열 (122-97+1 = 26)
    int i = 0, j = 0;               // 반복문에 사용할 변수들 초기화

    //배열 초기화
    for (i = 0; i < Key_z - Key_a + 1; i++) // i를 0부터 25까지 반복
    {
        random[i] = 0;             // 배열을 0으로 채움 (빈 칸 표시용 sentinel)
    }

    srand(time(NULL));             // 현재 시간을 시드로 난수 초기화(실행마다 다른 난수열)

    // 랜덤 셔플
    for (i = 0; i < Key_z - Key_a + 1; i++) // i: 0~25 -> 'a'+i 를 한 번씩 배치
    {
        while (1)                   // 비어 있는 위치가 나올 때까지 무한 반복
        {
            int rand_index = rand() % (Key_z - Key_a + 1); // 0~25 사이 임의 인덱스
            if (random[rand_index] == 0)  // 그 자리가 비어 있으면(초기값 0)
            {
                random[rand_index] = (char)(i + Key_a); // 'a'+i 문자를 그 자리에 넣음
                break;                 // 해당 i의 배치 완료 -> while 탈출
            }
        }
    }

    //------------ 더블 소팅 (버블 소트, swap 이용) ------------------------
    for (i = 0; i < Key_z - Key_a; i++)          // 바깥 루프: 총 25회(= n-1) 패스
    {
        for (j = 0; j < Key_z - Key_a - i; j++)  // 안쪽 루프: 인접한 쌍들 비교(끝쪽은 매 패스마다 확정되므로 범위 감소)
        {
            if (random[j] > random[j + 1])       // 앞 원소가 더 크면(사전순 뒤면)
            {
                swap(&random[j], &random[j + 1]); // 두 원소 자리 교환 -> 점점 큰 값이 뒤로 밀려남
            }
        }
    }

    //------------ 출력 ------------------------
    printf("\tindex\tsort");        // 헤더 출력 (정렬된 결과를 'sort'라는 이름으로 표기)
    for (i = 0; i < Key_z - Key_a + 1; i++) // 0~25까지
    {
        printf("\n\t%d\t%c", i, random[i]); // 인덱스와 해당 문자 출력 (여기서는 random이 정렬된 상태)
    }

    return 0;                       // 정상 종료
}
