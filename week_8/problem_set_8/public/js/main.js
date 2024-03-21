import { loadFormData, cleanFormData } from "./contact-form.js";

// create document click that watches the nav links only
document.addEventListener("click", (e) => {
  const { target } = e;
  if (!target.matches("#navbarSupportedContent a")) {
    return;
  }
  e.preventDefault();
  urlRoute();
});

const urlRoutes = {
  404: {
    template: "/templates/404.html",
    title: "404",
  },
  "/": {
    template: "/templates/home.html",
    title: "home",
  },
  "/pmtsz": {
    template: "/templates/pmtsz.html",
    title: "pmtsz",
  },
  "/contact": {
    template: "/templates/contact.html",
    title: "contact",
  },
};

const urlRoute = (event) => {
  event = event || window.event; // get window.event if event argument not provided
  event.preventDefault();
  window.history.pushState({}, "", event.target.href);
  urlLocationHandler();
};

function enableFormValidation() {
  let form = document.querySelector("#contact-form");
  form.addEventListener(
    "submit",
    function (event) {
      if (!form.checkValidity()) {
        event.preventDefault();
        event.stopPropagation();
      } else {
        localStorage.setItem("contactFormSubmitted", true);
        window.location.href = "/contact";
      }
      form.classList.add("was-validated");
    },
    false
  );
}

async function fetchAndDisplayHTML(path, elementId) {
  const html = await fetch(path).then((response) => response.text());
  document.getElementById(elementId).innerHTML = html;
}

async function handleContactRoute() {
  if (localStorage.getItem("contactFormSubmitted") === "true") {
    await fetchAndDisplayHTML("/templates/contact-success.html", "content");
    document
    .getElementById("new-contact-form")
    .addEventListener("click", cleanFormData);
  } else {
    await fetchAndDisplayHTML("/templates/contact.html", "content");
    loadFormData();
    enableFormValidation();
  }
}

const urlLocationHandler = async () => {
  let location = window.location.pathname;
  if (location.length == 0) {
    location = "/";
  }

  const route = urlRoutes[location] || urlRoutes["404"];

  if (location === "/contact") {
    handleContactRoute();
  } else {
    await fetchAndDisplayHTML(route.template, "content");
    document.title = route.title;
  }
};

// add an event listener to the window that watches for url changes
window.onpopstate = urlLocationHandler;
// call the urlLocationHandler function to handle the initial url
window.route = urlRoute;
// call the urlLocationHandler function to handle the initial url
urlLocationHandler();
