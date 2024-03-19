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

async function fetchAndDisplayHTML(path, elementId) {
  const html = await fetch(path).then((response) => response.text());
  document.getElementById(elementId).innerHTML = html;
}

// create a function that handles the url location
const urlLocationHandler = async () => {
  let location = window.location.pathname; // get the url path
  // if the path length is 0, set it to primary page route
  if (location.length == 0) {
    location = "/";
  }
  // get the route object from the urlRoutes object
  const route = urlRoutes[location] || urlRoutes["404"];

  if (location === "/contact") {
    if (localStorage.getItem("contactFormSubmitted") === "true") {
      await fetchAndDisplayHTML("/templates/contact-success.html", "content");
      document
        .getElementById("new-contact-form")
        .addEventListener("click", cleanFormData);
      console.log("aaa")
    } else {
      await fetchAndDisplayHTML("/templates/contact.html", "content");
      loadFormData();
      document
        .getElementById("contact-submit")
        .addEventListener("click", () => {
          localStorage.setItem("contactFormSubmitted", true);
          window.location.href = "/contact";
        });
      console.log("bbb")
    }
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
