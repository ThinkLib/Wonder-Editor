import { GameObject } from "amyjs/dist/es2015/core/Entity/GameObject";
import { Component } from "amyjs/dist/es2015/core/Component";

export const create = () => {
    return GameObject.create();
};

export const addComponent = (gameObject: GameObject, component: Component) => {
    gameObject.addComponent(component);
};

export const getTransform = (gameObject: GameObject) => {
    return gameObject.transform;
};


export const translate = (gameObject: GameObject, x: number, y: number, z: number) => {
    let transform = getTransform(gameObject);

    transform.translate(x, y, z);
};

export const rotate = (gameObject: GameObject, angle: number, x: number, y: number, z: number) => {
    let transform = getTransform(gameObject);

    transform.rotate(angle, x, y, z);
};
