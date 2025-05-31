import * as THREE from 'https://unpkg.com/three@0.161.0/build/three.module.js';
import { OrbitControls } from 'https://unpkg.com/three@0.161.0/examples/jsm/controls/OrbitControls.js';
import gsap from 'https://cdn.jsdelivr.net/npm/gsap@3.12.5/+esm';

// Scene setup ------------------------------------------------
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(60, innerWidth / innerHeight, 0.1, 100);
camera.position.set(0, 0, 7);

const renderer = new THREE.WebGLRenderer({ canvas: document.getElementById('scene'), antialias: true, alpha: true });
renderer.setPixelRatio(devicePixelRatio);
renderer.setSize(innerWidth, innerHeight);

// Geometry & material
const geo = new THREE.TorusKnotGeometry(1.5, 0.45, 200, 32);
const mat = new THREE.MeshStandardMaterial({ color: 0x00eaff, wireframe: true });
const torus = new THREE.Mesh(geo, mat);
scene.add(torus);

// Lighting
scene.add(new THREE.AmbientLight(0xffffff, 0.7));
const dir = new THREE.DirectionalLight(0xffffff, 0.4);
dir.position.set(5, 5, 5); scene.add(dir);

// Orbit controls (optional—remove for pure animation)
new OrbitControls(camera, renderer.domElement);

// GSAP animation loop
gsap.to(torus.rotation, { y: Math.PI * 2, duration: 12, repeat: -1, ease: 'none' });

function resize() {
    camera.aspect = innerWidth / innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(innerWidth, innerHeight);
}
window.addEventListener('resize', resize);

function tick() {
    renderer.render(scene, camera);
    requestAnimationFrame(tick);
}
tick();

// Navbar toggle ---------------------------------------------
const burger = document.querySelector('.burger');
const menu = document.querySelector('.menu');
burger.addEventListener('click', () => {
    const expanded = burger.getAttribute('aria-expanded') === 'true' || false;
    burger.setAttribute('aria-expanded', !expanded);
    menu.classList.toggle('open');
});
