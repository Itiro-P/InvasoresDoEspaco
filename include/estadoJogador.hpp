#pragma once

// Armazena vidas e pontos
class EstadoJogador {
    int vidas = 3;
    int pontos = 0;

    public:
    EstadoJogador() = default;
    void setVidas(const int vidas) { this->vidas = vidas; };
    void setPontos(const int pontos) { this->pontos += pontos; if(pontos % 1500 == 0 && pontos != 0 && vidas < 3) ++vidas; };
    void restaurarEstado() { vidas = 3; pontos = 0; };
    int getVidas() const { return vidas; };
    int getPontos() const  { return pontos; };
};