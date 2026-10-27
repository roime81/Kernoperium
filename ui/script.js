const body = document.body;
const toggle = document.getElementById('themeToggle');
const clock = document.getElementById('clock');

const updateClock = () => {
  const now = new Date();
  const time = now.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' });
  clock.textContent = time;
};

const setTheme = (theme) => {
  body.classList.remove('theme-kde', 'theme-gnome');
  body.classList.add(theme);
};

let currentTheme = 'theme-kde';
setTheme(currentTheme);
updateClock();
setInterval(updateClock, 30000);

toggle.addEventListener('click', () => {
  currentTheme = currentTheme === 'theme-kde' ? 'theme-gnome' : 'theme-kde';
  setTheme(currentTheme);
});
