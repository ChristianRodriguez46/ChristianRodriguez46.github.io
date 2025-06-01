// ========= Mobile Navigation Toggle ========= //
const menuToggle = document.getElementById("menu-toggle");
const body = document.body;

menuToggle.addEventListener("click", () => {
    body.classList.toggle("nav-open");
});

// ========= Close menu when clicking a link (mobile UX) ========= //
const navLinks = document.querySelectorAll(".nav-links a");
navLinks.forEach(link =>
    link.addEventListener("click", () => {
        body.classList.remove("nav-open");
    })
);