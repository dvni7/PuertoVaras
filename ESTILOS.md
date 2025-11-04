# 🎨 Guía Visual de Estilos de Menú

## Cambiar el Estilo del Menú

En `PuertoVaras.ino`, línea 28:
```cpp
#define MENU_STYLE 3  // <-- Cambia este número (1, 2 o 3)
```

---

## Estilo 1: TERMINAL 🖥️

```
#define MENU_STYLE 1
```

### Características:
- **Fuente**: Share Tech Mono (monoespaciada)
- **Estética**: Terminal retro, estilo hacker
- **Colores**: 
  - Fondo: Negro profundo (#0F0701)
  - Bordes: Naranja (#FF6B35)
  - Texto: Naranja/Ámbar
- **Elementos**:
  - Borde de terminal con efecto box-shadow
  - Números entre corchetes [1] [2]
  - Prompts tipo consola con ">"
  - Animación de hover con desplazamiento horizontal

### Ideal para:
- Estética cyberpunk/retro
- Proyectos con temática tech
- Usuarios que prefieren interfaces minimalistas

---

## Estilo 2: MODERN CARDS 💎

```
#define MENU_STYLE 2
```

### Características:
- **Fuente**: Poppins (moderna, sans-serif)
- **Estética**: Minimalista, glassmorphism
- **Colores**:
  - Fondo: Gradiente oscuro con animación pulse
  - Cards: Fondo translúcido con blur
  - Acentos: Gradiente naranja/ámbar
- **Elementos**:
  - Cards con backdrop-filter blur
  - Iconos emoji grandes (🔧 🤖)
  - Efectos de shimmer en hover
  - Elevación 3D al hacer hover
  - Animación radial en el fondo

### Ideal para:
- Presentaciones profesionales
- Interfaces modernas
- Usuarios que buscan elegancia

---

## Estilo 3: MAKER CAMPUS 🎓

```
#define MENU_STYLE 3  // <-- ESTILO POR DEFECTO
```

### Características:
- **Fuente**: Orbitron (futurista, geométrica)
- **Estética**: Branding institucional, profesional
- **Colores**:
  - Barra superior con gradiente naranja
  - Logo con efecto de texto degradado
  - Bordes gruesos (3px)
- **Elementos**:
  - Barra superior "MAKER CAMPUS - INNOVATION LAB"
  - Logo grande con degradado animado
  - Cards con efectos de fill desde abajo
  - Iconos emoji grandes (⚙️ 🎮)
  - Panel de información en la parte inferior
  - Divisor decorativo entre secciones

### Ideal para:
- Representación oficial de Maker Campus
- Demostraciones institucionales
- Mayor reconocimiento de marca

---

## 📐 Comparación Rápida

| Característica | Terminal | Modern | Campus |
|----------------|----------|---------|---------|
| **Complejidad** | Baja | Media | Alta |
| **Animaciones** | Mínimas | Medias | Altas |
| **Profesionalismo** | ★★☆☆☆ | ★★★★☆ | ★★★★★ |
| **Originalidad** | ★★★★☆ | ★★★☆☆ | ★★★★★ |
| **Carga rápida** | ★★★★★ | ★★★★☆ | ★★★☆☆ |
| **Legibilidad** | ★★★★★ | ★★★★☆ | ★★★★☆ |

---

## 🎯 Recomendaciones de Uso

### Para Desarrollo/Testing
→ **Estilo 1 (Terminal)**
- Carga más rápida
- Menos recursos
- Visual claro

### Para Demostraciones
→ **Estilo 2 (Modern)**
- Impresionante visualmente
- Apariencia profesional
- Balance perfecto

### Para Presentaciones Oficiales
→ **Estilo 3 (Campus)** ⭐ RECOMENDADO
- Identidad de marca fuerte
- Más completo y detallado
- Muestra el logo y nombre del proyecto

---

## 💡 Tips

1. **Rendimiento**: Si la ESP32 va lenta, usa el estilo 1 (más ligero)
2. **Impresionar**: Para mostrar el proyecto, usa el estilo 3
3. **Tablets**: Todos los estilos son responsive y táctil-friendly
4. **Personalización**: Puedes editar `menu_principal.h` para crear tu propio estilo

---

## 🔄 Cómo Cambiar el Estilo

1. Abre `PuertoVaras.ino` en Arduino IDE
2. Busca la línea 28:
   ```cpp
   #define MENU_STYLE 3
   ```
3. Cambia el número a 1, 2 o 3
4. Guarda y vuelve a subir el código a la ESP32
5. Reconecta y recarga `http://192.168.4.1`

¡Listo! El nuevo estilo estará activo.

---

## 🎨 Personalizar Colores

Si quieres cambiar los colores, edita `menu_principal.h`:

### Terminal (MENU_STYLE_TERMINAL)
```css
border: 3px solid #FF6B35;  /* Color del borde */
color: #FF6B35;              /* Color del texto */
```

### Modern (MENU_STYLE_MODERN)
```css
background: linear-gradient(135deg, #FF6B35 0%, #F7931E 100%);
```

### Campus (MENU_STYLE_CAMPUS)
```css
background: linear-gradient(90deg, #FF6B35 0%, #F7931E 100%);
```

---

**Maker Campus © 2025** | Puerto Varas Project
