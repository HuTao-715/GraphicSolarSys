#pragma once
#include <GL/glut.h>
#include <Windows.h>
void selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
        charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}
void drawCNString(const char* str) {
    int len, i;
    wchar_t* wstring;
    HDC hDC = wglGetCurrentDC();
    GLuint lista = glGenLists(1);

    // �����ַ��ĸ���
    // �����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
    // ����һ���ֽ���һ���ַ�
    len = 0;
    for (i = 0; str[i] != '\0'; ++i)
    {
        if (IsDBCSLeadByte(str[i]))
            ++i;
        ++len;
    }
    // ������ַ�ת��Ϊ���ַ�
    wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
    wstring[len] = L'\0';
    // �������ַ�
    for (i = 0; i < len; ++i)
    {
        wglUseFontBitmapsW(hDC, wstring[i], 1, lista);
        glCallList(lista);
    }
    // ����������ʱ��Դ
    free(wstring);
    glDeleteLists(lista, 1);
}