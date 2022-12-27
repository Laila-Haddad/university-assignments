
window.onload = () => {
  activeNav();
}

window.onscroll = () => {
  activeNav();
  stickyBar();
};


//nav 
function activeNav() {
  const section = document.querySelectorAll(".content > div");
  const menu = document.querySelectorAll("header nav li a");
  var scrolly = window.scrollY;
  // var fooTop= document.getElementById('Food').offsetTop - 80;
  var abTop= document.getElementById('About').offsetTop - 80;

  section.forEach((i) => {
   
    var top = i.offsetTop - 80;
    var height = i.offsetHeight;
    var id = i.getAttribute("id");


    if (scrolly >= top && scrolly < top + height) {
      menu.forEach((link) => {
        link.classList.remove("active");
        document
          .querySelector("header nav li a[href*=" + id + "]")
          .classList.add("active");
      });
    }
    else {
      if (scrolly <=abTop) {
        menu.forEach((link) => {link.classList.remove("active");});
        document
        .getElementsByClassName('home')[0]
        .classList.add("active");
      }
    }
  });


  if (scrolly >abTop - 300){
    document.getElementsByTagName('nav')[0].style.backgroundColor='var(--Grey)';
    document.getElementById('Logo').style.width='110px'
  }
  else {
    document.getElementsByTagName('nav')[0].style.backgroundColor='';
    document.getElementById('Logo').style.width='170px';
  }
}




//review block
let slideIndex = 2;
showSlides(slideIndex);

function plusSlides(n) {
  showSlides(slideIndex += n);
}

function currentSlide(n) {
  showSlides(slideIndex = n);
}

function showSlides(n) {
  let i;
  let slides = document.getElementsByClassName("review");
  let dots = document.getElementsByClassName("dot");

  if (n > slides.length) {slideIndex = 1}
  if (n < 1) {slideIndex = slides.length}

  for (i = 0; i < slides.length; i++) {
    slides[i].style.display = "none";
    dots[i].classList.remove('dot-active');
  }
  
  slides[slideIndex-1].style.display = 'flex';
  dots[slideIndex-1].classList.add('dot-active');
} 




//catgory band from menu page
var cat = document.getElementById('categories');
const sticky = cat.offsetTop - 70;

function stickyBar() {
  if (window.scrollY >= sticky) {
    cat.style.position = 'fixed';
    cat.style.top = '70px';
  }
  else {
    cat.style.position = 'absolute';
    cat.style.top = '240px';
  }
}

