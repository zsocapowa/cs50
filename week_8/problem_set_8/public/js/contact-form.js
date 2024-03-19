export function loadFormData() {
    const location = window.location.pathname;
    if (location != '/contact') {
        return;
    }
    const storedData = localStorage.getItem('contactFormData');

    if (storedData) {
        const formData = JSON.parse(storedData);

        for (const [key, value] of Object.entries(formData)) {
            document.querySelector(`#${key}`).value = value
        }
    }
};


export function cleanFormData() {
    localStorage.removeItem("contactFormData");
    localStorage.removeItem("contactFormSubmitted");
}

document.addEventListener("change", (e) => {
    const { target } = e;
    if (!target.matches("#contact-form input, #contact-form textarea")) {
        return;
    }
    e.preventDefault();
    saveFormData(target)
});


function saveFormData(target) {
    let formData = {};
    const storedData = localStorage.getItem('contactFormData');
    if (storedData === null) {
        formData[target.id] = target.value;
    }
    else {
        formData = JSON.parse(storedData);
        formData[target.id] = target.value;
    }
    localStorage.setItem('contactFormData', JSON.stringify(formData));
}
